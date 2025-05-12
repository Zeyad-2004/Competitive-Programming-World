
int kadane(const vector<int>& arr) {
    int max_current = arr[0];
    int max_global = arr[0];

    for (size_t i = 1; i < arr.size(); ++i) {
        max_current = max(arr[i], max_current + arr[i]);
        max_global = max(max_global, max_current);
    }

    return max_global;
}