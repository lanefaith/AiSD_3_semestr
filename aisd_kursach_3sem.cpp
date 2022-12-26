#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


class Tree {
public:

	static const int n = 256;
	int count[n]{};
	unsigned char letter[n]{};
	unsigned char to_encrypt[n]{};
	unsigned char to_decipher[n]{}; 

	class Node {
	public:
		char cur;
		int c;
		Node* next;
		int type;
		Node(int a, char b) {
			c = a;
			cur = b;
			next = 0;
			type = 2;
		}
	};

	vector <Node*> high;

	void clear() {
		for (int i = 0; i < n; i++) {
			letter[i] = char(i);
			count[i] = to_encrypt[i] = to_decipher[i] = 0;
		}
	}

	void sort() {
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (count[letter[i]] < count[letter[j]])
					swap(letter[i], letter[j]);
	}

	void read_file(string from) {
		clear();
		ifstream cin(from);
		unsigned char t;
		while (1) {
			t = cin.get();
			if (cin.eof()) break;
			count[t]++;
		}
		cin.close();
		sort();
		create(); 
	}

	void encrypt(string from, string to) {
		ifstream cin(from);
		ofstream cout(to);
		unsigned char t;
		while (1) {
			t = cin.get();
			if (cin.eof()) break;
			cout << to_encrypt[t];
		}
		cin.close(); cout.close();
	}
	void decipher(string from, string to) {
		ifstream cin(from);
		ofstream cout(to);
		unsigned char t;
		while (1) {
			t = cin.get();
			if (cin.eof()) break;
			cout << to_decipher[t];
		}
		cout.close(); cin.close();
	}

	void dictioneries(ofstream& binary, ofstream& new_letters) {
		binary << "the code of each symbol defined by the huffman algorithm:\n";
		new_letters << "on the left are the original symbols, and on the right are encrypted:\n";
		for (int i = 0; i < high.size(); i++) {
			Node* temp = high[i];
			int bin;
			string bin_code = "";
			while (temp->type != 2) { 
				bin = temp->type;
				string s = to_string(bin);
				bin_code = s + bin_code;
				temp = temp->next;
			}
			binary << high[i]->cur << " " << bin_code << "\n";
			temp = high[i];
			int mask = 0;
			int k = 0;
			while (temp->type != 2) { 
				mask += (temp->type << k);  
				k++;
				temp = temp->next;
			}
			while (k++ < 7)
				mask *= 2;
			new_letters << high[i]->cur << "  " << char(mask) << "\n";
		}
	}

	void sort_nodes(vector <Node*>& a) {
		int size_ = a.size();
		for (int i = 0; i < size_; i++)
			for (int j = i + 1; j < size_; j++)
				if (a[i]->c > a[j]->c)
					swap(a[i], a[j]);
	}

	void create() {
		vector <Node*> current; 
		for (int i = 0; i < n; i++) {
			if (!count[letter[i]]) continue;
			Node* temp = new Node(count[letter[i]], letter[i]);
			high.push_back(temp);
			current.push_back(temp);
		}

		while (current.size() > 1) { //O(n * n^2)
			sort_nodes(current);

			current[0]->type = 0;
			current[1]->type = 1; 
			Node* temp = new Node(current[0]->c + current[1]->c, current[0]->cur); 
			current[0]->next = temp; 
			current[1]->next = temp;
			current.erase(current.begin()); 
			current.erase(current.begin());
			current.push_back(temp);
		}
		int was[n]{};
		for (int i = 0; i < high.size(); i++) {
			int mask = 0;
			unsigned char letter = high[i]->cur;
			int k = 0;
			Node* temp = high[i];
			while (temp->type != 2) { 
				mask += (temp->type << k); 
				k++;
				temp = temp->next;
			}
			while (k++ < 7)
				mask *= 2;

			if (was[mask]) cout << "Warning\n" << to_encrypt[letter] << " " << to_decipher[mask] << endl; 
			was[mask]++;
			//cout << mask << " " << letter - 0 << " " << letter << endl;
			to_encrypt[letter] = char(mask); // отмечаем в словариках 
			to_decipher[mask] = letter;
		}
	}
};

int main()
{
	Tree a;
	ofstream binary("bin_codes.txt");
	ofstream new_letters("crypt.txt");
	a.read_file("input.txt");
	a.encrypt("input.txt", "output_encrypt.txt");
	a.decipher("output_encrypt.txt", "output_decipher.txt");
	a.dictioneries(binary, new_letters);
	binary.close();
	new_letters.close();
	cout << "Chek the files of results\n";
	return 0;
}