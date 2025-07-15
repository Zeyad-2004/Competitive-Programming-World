void print_int128(__int128 n) {
    if (n == 0) {
        cout << "0";
        return;
    }
    string s;
    while (n > 0) {
        s += '0' + (n % 10);
        n /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}