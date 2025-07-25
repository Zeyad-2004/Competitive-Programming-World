struct segmentTree{
    int size;
    vector<int> values;
    void init(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        values.assign(2 * size, INT_MAX);
    }

    void build(vector<int> &nums, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int)nums.size()) {
                values[x] = nums[lx];
            }
            return;
        }

        int mid = (rx + lx) / 2;
        build(nums, 2 * x + 1, lx, mid);
        build(nums, 2 * x + 2, mid, rx);

        values[x] = min(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int> &nums){
        build(nums, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            values[x] = v;
            return;
        }
        int mid = (rx + lx) / 2;
        if(i < mid){
            set(i, v, 2 * x + 1, lx, mid);
        }
        else{
            set(i, v, 2 * x + 2, mid, rx);
        }
        values[x] = min(values[2 * x + 1], values[2 * x + 2]);
    }
    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    long long mn(int l, int r, int x, int lx, int rx){
        if(l >= rx || lx >= r) return INT_MAX;
        if(lx >= l && rx <= r) return values[x];

        int mid = (rx + lx) / 2;
        long long a = mn(l, r, 2 * x + 1, lx, mid);
        long long b = mn(l, r, 2 * x + 2, mid, rx);

        return min(a, b);
    }

    long long mn(int l, int r){
        return mn(l, r, 0, 0, size);
    }

    // Use it to get the first index that is smaller than v in the range [l, r) ___ (V not included)
    // Make sure that segmentTree built with min operation
    void getFirstIndexSmallerThan_V_Between_L_R(int v, int l, int r, int x, int lx, int rx, int &ans){
        if(~ans || values[x] > v) return;
        if(l >= rx || lx >= r) return;
        if(rx - lx == 1){
            if(values[x] < v) ans = lx; // Make "<" --> "<=" if you want to include the value v

            return;
        }

        int mid = (rx + lx) / 2;

        // Make "<" --> "<=" if you want to include the value v
        if(values[2 * x + 1] < v){
            getFirstIndexSmallerThan_V_Between_L_R(v, l, r, 2 * x + 1, lx, mid, ans);
        }

        // Make "<" --> "<=" if you want to include the value v
        if(values[2 * x + 2] < v && !~ans){
            getFirstIndexSmallerThan_V_Between_L_R(v, l, r, 2 * x + 2, mid, rx, ans);
        }

    }

    long long getFirstIndexSmallerThan_V_Between_L_R(int v, int l, int r){
        int ans = -1;
        getFirstIndexSmallerThan_V_Between_L_R(v, l, r, 0, 0, size, ans);
        return ans;
    }
};