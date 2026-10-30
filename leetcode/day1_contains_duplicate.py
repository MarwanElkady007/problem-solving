"""
Problem Solving — Day 1: Contains Duplicate (LeetCode 217)
Category: Arrays & Hashing | Pattern: Hash Set
Target Time Complexity: O(n) | Space Complexity: O(n)
"""

from typing import List

class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        """
        Intuition:
        - A hash set provides average O(1) time complexity for insertions and lookups.
        - As we iterate through nums, if an element already exists in the seen set,
          we have found a duplicate -> return True immediately.
        - If we finish iterating without finding any repeats, return False.
        """
        seen = set()
        for num in nums:
            if num in seen:
                return True
            seen.add(num)
        return False


def test_solution():
    sol = Solution()
    
    test_cases = [
        ([1, 2, 3, 1], True),
        ([1, 2, 3, 4], False),
        ([1, 1, 1, 3, 3, 4, 3, 2, 4, 2], True)
    ]
    
    for i, (nums, expected) in enumerate(test_cases, 1):
        result = sol.containsDuplicate(nums)
        assert result == expected, f"Failed on test case {i}: expected {expected}, got {result}"
        print(f"Test case {i} passed: nums={nums} -> {result}")

    print("\nAll tests passed successfully!")

if __name__ == "__main__":
    test_solution()
