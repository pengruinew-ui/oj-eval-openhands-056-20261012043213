#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

struct Interval {
    int l, r;
    bool operator<(const Interval& other) const {
        return l < other.l || (l == other.l && r < other.r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    set<Interval> intervals;
    
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        
        if (op == 'A') {
            int l, r;
            cin >> l >> r;
            
            int deleted_count = 0;
            
            // Find intervals that overlap with [l, r]
            auto it = intervals.lower_bound({l, r});
            
            // Check intervals to the left of the found position
            vector<Interval> to_delete;
            
            // Check intervals that might overlap from the left
            if (it != intervals.begin()) {
                auto left_it = it;
                left_it--;
                while (true) {
                    if (left_it->r >= l) {
                        to_delete.push_back(*left_it);
                        if (left_it == intervals.begin()) {
                            break;
                        }
                        left_it--;
                    } else {
                        break;
                    }
                }
            }
            
            // Check intervals from current position onwards
            auto right_it = it;
            while (right_it != intervals.end() && right_it->l <= r) {
                to_delete.push_back(*right_it);
                right_it++;
            }
            
            // Delete all overlapping intervals
            for (const auto& interval : to_delete) {
                intervals.erase(interval);
                deleted_count++;
            }
            
            // Insert the new interval
            intervals.insert({l, r});
            
            cout << deleted_count << "\n";
            
        } else if (op == 'B') {
            cout << intervals.size() << "\n";
        }
    }
    
    return 0;
}