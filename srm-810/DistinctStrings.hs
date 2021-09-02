module DistinctStrings where

generate :: Int -> String -> Int -> [String]
generate passLen alphabet numPass = take numPass $ go passLen
  where
    go 1 = return <$> alphabet
    go passLen = alphabet >>= (<$> go (passLen - 1)) . (:)

----------

main :: IO ()
main = do
  print $ generate 5 "abcde" 10
  print $ generate 2 "1a2b" 4
  print $ generate 3 "abcdefghijklmnopqrtuvxyz1234567890" 40
