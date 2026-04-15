#include <bits/stdc++.h>
using namespace std;

/*
Problem: Minimum Operations to Adjust Array (Prime Constraint)
Platform: LeetCode

Approach:
- Precompute primes using Sieve of Eratosthenes
- Store all prime numbers in a list

Rules:
1. Even index (i % 2 == 0):
    → number must be prime
    → if not prime:
        increase to next prime

2. Odd index:
    → number must be non-prime
    → if prime:
        increase by:
            +1 normally
            +2 if number is 2 (since 3 is prime)

Steps:
1. Build sieve up to max value
2. Store primes in array
3. Iterate over nums:
    - Apply rules
    - Accumulate operations

Time Complexity:
O(N log log N + N log N)

Space Complexity:
O(N)

Concepts Used:
- Sieve of Eratosthenes
- Binary search (lower_bound)
- Greedy modification
*/

class Solution {
public:
    int minOperations(vector<int>& nums) {

        // Step 1: Sieve
        vector<long long> prime(100100, 1);
        prime[0] = 0;
        prime[1] = 0;

        vector<long long> ans; // store primes

        for (long long i = 2; i < prime.size(); i++) {
            if (prime[i] == 1) {
                ans.push_back(i);

                for (long long j = i * i; j < prime.size(); j += i) {
                    prime[j] = 0;
                }
            }
        }

        long long total = 0;

        // Step 2: Process array
        for (long long i = 0; i < nums.size(); i++) {

            // Even index → must be prime
            if (i % 2 == 0) {

                if (prime[nums[i]] != 1) {

                    // Find next prime
                    long long index =
                        lower_bound(ans.begin(), ans.end(), nums[i]) - ans.begin();

                    total += (ans[index] - nums[i]);
                }
            }

            // Odd index → must be non-prime
            else {

                if (prime[nums[i]] == 1) {

                    if (nums[i] == 2) {
                        total += 2; // 2 → 4
                    } else {
                        total += 1; // make non-prime
                    }
                }
            }
        }

        return (int)total;
    }
};