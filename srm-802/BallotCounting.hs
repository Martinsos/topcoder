#!/usr/bin/env stack
-- stack script --resolver lts-17.9 --package hspec --package strongpath

import Test.Hspec

count :: String -> Int
count = go (0, 0)
  where
    go :: (Int, Int) -> String -> Int
    go _ [] = 0
    go (as, bs) votes = if abs (as - bs) > (length votes) then 0
        else let asbs' = if head votes == 'A' then (as + 1, bs) else (as, bs + 1)
             in 1 + go asbs' (tail votes)

main :: IO ()
main = hspec $ mapM_ (\tc -> it (show tc) $ runTest tc) testCases
  where
    runTest testCase = count (fst testCase) `shouldBe` snd testCase
    testCases =
        [ ("AAAAABBBBB", 10)
        , ("AAAAABBBBA", 10)
        , ("AAAAA", 3)
        , ("AAAAAA", 4)
        , ("AABAABAAB", 7)
        , ("BABABBB", 6)
        ]
