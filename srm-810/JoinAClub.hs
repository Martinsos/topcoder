module JoinAClub where

-- Solution:
-- This is really a graph with numKids nodes and connections are friendships.
-- We need to find the biggest connected component of the graph and then
-- return any traversal.
-- Since constraints are not big, this can be done relatively easily, no
-- special optimizations / care are needed.

maximumClub :: Int -> [(Int, Int)] -> [Int]
maximumClub numKids friendships = undefined

main :: IO ()
main = do
  print "Hi"
