module ModularQuadrant (sum') where

sum' :: Int -> Int -> Int -> Int -> Integer
sum' r1 r2 c1 c2 = sumRect (r2, c2) - sumRect (r1 - 1, c2) - sumRect (r2, c1 - 1) + sumRect (r1 - 1, c1 - 1)

numAppear :: (Integral a) => a -> a
numAppear n | n <= 0 = 0
            | otherwise = n `div` 3 + (if n `mod` 3 == 0 then 0 else 1)

sumNum :: (Integral a) => a -> a -> a -> a
sumNum start step n | n <= 0 = 0
                    | otherwise = start * n + step * (n - 1) * n `div` 2

sumRect :: (Int, Int) -> Integer
sumRect (r, c)
  | r < 0 || c < 0 = 0
  | r > c = sumRect (c, r)
  | otherwise = sumRectPart + 2 * sumTrngPart - sumTrngDiag
  where
    (r', c') = (fromIntegral r :: Integer, fromIntegral c :: Integer)
    sumRectPart = (* h) $ sum $ map (\d -> ((h + d) `mod` 3) * numAppear(w - d)) [0..2]
      where (h, w) = (r' + 1, c' - r')
    sumTrngPart = sumNum 2 3 (numAppear r') + 2 * (sumNum 3 3 (numAppear (r' - 1)))
    sumTrngDiag = numAppear r' + 2 * (numAppear (r' - 1))
