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
};