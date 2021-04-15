module BallotCounting
    (count
    ) where

import Data.List (partition)

count :: String -> Int
count = go (0, 0)
  where
    go :: (Int, Int) -> String -> Int
    go _ [] = 0
    go (as, bs) votes = if abs (as - bs) > (length votes) then 0
        else let asbs' = if head votes == 'A' then (as + 1, bs) else (as, bs + 1)
             in 1 + go asbs' (tail votes)


test :: IO Bool
test = do
    -- NOTE: This block shouldn't change from problem to problem.
    let executedTests = map (\t -> (runTestCase count t, t)) testCases
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
    runTestCase f testCase = let result = f $ fst testCase
                                 expected = snd testCase
                                 passed = result == expected
                             in (passed, (result, expected))
    testCases =
        [ ("AAAAABBBBB", 10)
        , ("AAAAABBBBA", 10)
        , ("AAAAA", 3)
        , ("AAAAAA", 4)
        , ("AABAABAAB", 7)
        , ("BABABBB", 6)
        ]
