module MagicNumbersAgain (count) where

digits x = if x == 0 then [0] else reverse $ digitsRev x
  where digitsRev 0 = []
        digitsRev x = (x `mod` 10) : (digitsRev $ x `div` 10)

count :: Integer -> Integer -> Int
count a b = length $ filter (isMagicNumber . (^2)) [(ceiling $ sqrt (fromIntegral a))..(floor $ sqrt (fromIntegral b))]
  where
    isMagicNumber = areDigitsMagic True . reverse . digits
    areDigitsMagic isSmaller (d1:d2:ds) = (if isSmaller then d1 < d2 else d1 > d2) && areDigitsMagic (not isSmaller) (d2:ds)
    areDigitsMagic _ _ = True
