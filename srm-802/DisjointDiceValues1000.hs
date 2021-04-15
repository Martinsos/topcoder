module DisjointDiceValue1000
    () where

import Data.List (partition)

getProbability :: Int -> Int -> Double
getProbability _ _ = 0.42


test :: IO Bool
test = do
    -- NOTE: This block shouldn't change from problem to problem.
    let executedTests = map (\t -> (runTestCase getProbability t, t)) testCases
    let (passedTests, failedTests) = partition (fst . fst) executedTests
    putStrLn "((<passed>, (<result>, <expected>)), <test_case>)"
    putStrLn "Passed tests:"
    mapM_ (putStrLn . show) passedTests
    putStrLn "Failed tests:"
    mapM_ (putStrLn . show) failedTests
    if null failedTests
        then putStrLn "SUCCESS: All tests passed!" >> return True
        else putStrLn "FAILURE: Some tests failed." >> return False
  where
    -- NOTE: Logic below is specific per problem.
    runTestCase f testCase = let result = uncurry f $ fst testCase
                                 expected = snd testCase
                                 passed = abs (result - expected) <= 0.000000001
                             in (passed, (result, expected))
    testCases =
        [ ((1, 1), 1 / 6)
        , ((4, 1), 0.5177469135802468)
        , ((1, 4), 0.5177469135802468)
        , ((3, 3), 0.7910236625514401)
        ]
