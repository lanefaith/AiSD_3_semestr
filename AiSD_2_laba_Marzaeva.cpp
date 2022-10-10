#include <iostream>
#include <algorithm>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <ctime>

using namespace std;

const unsigned N = 100000;

ifstream f("input.txt");

struct snail {
    int x, y; // snail coordinates
}
a[N], b[N];  // arrays storing data about the location of snails

bool answer = 1;
int distance_snail = 9999999;

bool sortf(snail one, snail another) {

    return one.x < another.x or (one.x == another.x and one.y < another.y);
}

int dist(snail one, snail another) { // finding the square of the length of the distance between the snails along a right triangle
    return (one.x - another.x) * (one.x - another.x) + (one.y - another.y) * (one.y - another.y);
}


int search(int l, int r, snail(&a)[N]) { // finding the square of the length of the distance between the snails
    if (r - l <= 2) {
        if (a[r - 1].y < a[l].y) swap(a[r - 1], a[l]);// sorting by y
        if (r - l == 1) return 9999999;
        else return dist(a[l], a[r - 1]);
    }

    int h1 = search(l, (l + r) / 2, a);
    int h2 = search((l + r) / 2, r, a);
    int h = min(h1, h2); // finding the minimum
    if (distance_snail > h) {
        distance_snail = h;
    }


    int left = l;
    int middle = (l + r) / 2;

    for (int i = l; i < r; i++) {
        if (left == (l + r) / 2) b[i] = a[middle++];
        else if (middle == r) b[i] = a[left++];
        else if (a[middle].y < a[left].y) b[i] = a[middle++];
        else b[i] = a[left++];
    }
    for (int i = l; i < r; i++) {
        a[i] = b[i];
    }
    vector <snail> S;
    for (int i = l; i < r; i++) {
        if (abs(a[(l + r) / 2].x - a[i].x) * abs(a[(l + r) / 2].x - a[i].x) <= h) {
            S.push_back(a[i]);
        }
    }

    int ans = h;

    for (int i = 0; i < S.size(); i++) {
        int x = 0;
        for (int j = i + 1; j < S.size(); j++) {
            if (abs(S[i].y - S[j].y) * abs(S[i].y - S[j].y) <= h) {
                ans = min(ans, dist(S[i], S[j]));
                if (distance_snail == dist(S[i], S[j])) x++;
                else if (distance_snail > ans) {
                    x = 1;
                    distance_snail = ans;
                }
            }
            else break;
        }
        for (int j = i - 1; j >= 0; j--) {
            if (abs(S[i].y - S[j].y) * abs(S[i].y - S[j].y) <= h) {
                ans = min(ans, dist(S[i], S[j]));
                if (distance_snail == dist(S[i], S[j])) x++;
                else if (distance_snail > ans) {
                    x = 1;
                    distance_snail = ans;
                }
            }
            else break;
        }
        if (x > 1) { 
            answer = 0;
        }
        else { 
            answer = 1;
        }
    }
    return min(ans, h);
}

int main()
{
    unsigned int start_time = clock(); // the initial time of the program
    int time_of_snails = 0;
    setlocale(0, "ru");
    int n;
    f >> n; // entering the number of snails
    for (int i = 0; i < n; i++) { // entering snail coordinates
        f >> a[i].x >> a[i].y;
      // cout << "Координаты улитки № " << i + 1 << ": " << a[i].x << " " << a[i].y << "\n";
    }

    sort(a, a + n, sortf); // sorting by x
    int ans = search(0, n, a); // finding the square of the length of the distance between the snails

    if (answer == 1) {
        if (distance_snail != 0)
        {
            cout << "Кратчайшее расстояние между улитками: " << sqrt(distance_snail * 1.0);
            cout << "\nВремя, через которая встретились первые улитки: " << (sqrt(distance_snail * 1.0)) / 2;
        }
        else
            cout << "\nИзначальные координаты некоторых улиток совпадают\n";
    }
    else {
        cout << "Улитки в замешательстве";
    }
    unsigned int end_time = clock(); // the end time of the program
    unsigned int search_time = end_time - start_time; // the required time of the program
    cout << endl << "Время работы программы: " << search_time;
    return 0;
}