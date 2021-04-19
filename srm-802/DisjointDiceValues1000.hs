#!/usr/bin/env stack
-- stack script --resolver lts-17.9 --package hspec

import Test.Hspec

getProbability :: Int -> Int -> Double
getProbability _ _ = 0.42

main :: IO ()
main = hspec $ mapM_ (\tc -> it (show tc) $ runTest tc) testCases
  where
    runTest testCase = abs ((uncurry getProbability) (fst testCase) - snd testCase) <= 0.000000001
    testCases =
        [ ((1, 1), 1 / 6)
        , ((4, 1), 0.5177469135802468)
        , ((1, 4), 0.5177469135802468)
        , ((3, 3), 0.7910236625514401)
        ]
