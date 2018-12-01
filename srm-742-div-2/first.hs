module BirthdayCandy (mostCandy) where

mostCandy :: Int -> [Int] -> Int
mostCandy k = maximum . map (\c -> c `div` (k + 1) + c `mod` (k + 1))

-- Alternative solution, having fun with applicative functors.
mostCandy' :: Int -> [Int] -> Int
mostCandy' k = maximum . map ((+) <$> (`div` (k + 1)) <*> (`mod` (k + 1)))
