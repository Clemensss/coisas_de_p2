import Data.List
import System.IO

--insertionSort :: [Int] -> [Int]
--insertionSort (x:xs) =  

insertionLoop :: Int -> Int -> [Int] -> Int
insertionLoop i 0 (x:xs) = 0
insertionLoop i j (x:xs) = key 

index :: [Int] -> Int -> Int
index [x] i = x
index (x:xs) 0 = x
index (x:xs) i = index xs (i-1) 

main = do
	let wow = index thing 4
	print wow
