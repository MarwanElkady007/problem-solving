"""
Problem Solving — Day 2: Valid Anagram (LeetCode 242)
Category: Arrays & Hashing | Pattern: Hash Map / Frequency Count
Target Time Complexity: O(n) | Space Complexity: O(1) [at most 26 lowercase English letters]
"""

class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        """
        Intuition:
        1. If lengths are different, they cannot be anagrams -> False.
        2. Count frequency of each character in s and in t.
        3. If character frequencies match exactly, return True.
        """
        if len(s) != len(t):
            return False
            
        countS, countT = {}, {}
        
        for i in range(len(s)):
            countS[s[i]] = 1 + countS.get(s[i], 0)
            countT[t[i]] = 1 + countT.get(t[i], 0)
            
        return countS == countT


def test_solution():
    sol = Solution()
    test_cases = [
        ("anagram", "nagaram", True),
        ("rat", "car", False),
        ("a", "ab", False)
    ]
    for i, (s, t, expected) in enumerate(test_cases, 1):
        result = sol.isAnagram(s, t)
        assert result == expected, f"Failed on test {i}: expected {expected}, got {result}"
        print(f"Test case {i} passed: ('{s}', '{t}') -> {result}")

    print("\nAll tests passed successfully!")

if __name__ == "__main__":
    test_solution()
