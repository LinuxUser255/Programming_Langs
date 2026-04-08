main :: IO ()
main = do
    mapM_ print [0..4]                     -- for-loop equivalent
    mapM_ (\x -> putStrLn $ "Item: " ++ show x) ["apple", "banana"]
