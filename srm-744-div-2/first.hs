module ThreePartSplit (split) where

split :: Int -> Int -> [Int]
split a d = let m = (d - a) `div` 3 in [a + m, a + 2 * m]
