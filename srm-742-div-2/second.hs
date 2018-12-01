module SixteenQueens (addQueens) where

addQueens :: [Int] -> [Int] -> Int -> [Int]
addQueens row col 0 = []
addQueens row col add = rAdd:cAdd:(addQueens (rAdd:row) (cAdd:col) (add - 1))
  where (rAdd, cAdd):_ = [(r, c) | r <- [0..49], c <- [0..49], not (isUnderAttack (r, c))]
        isUnderAttack (r, c) = any (\(r', c') -> r == r' || c == c' || abs (r - r') == abs (c - c')) (zip row col)
