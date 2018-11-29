module SixteenQueens (addQueens) where

addQueens :: [Int] -> [Int] -> Int -> [Int]
addQueens rows cols 0 = []
addQueens rows cols add = rAdd:cAdd:(addQueens (rAdd:rows) (cAdd:cols) (add - 1))
  where (rAdd, cAdd):_ = [(r, c) | r <- [0 .. boardSize - 1], c <- [0 .. boardSize - 1], not (isUnderAttack (r, c))]
        isUnderAttack (r, c) = any (\(r', c') -> r == r' || c == c' || abs (r - r') == abs (c - c')) (zip rows cols)
        boardSize = 50
