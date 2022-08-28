 def count(chessBoard):
     width = len(chessBoard[0])
     height = len(chessBoard)
     nums = [0] * (len(chessBoard) + 1)#malloc :p
     result = {}   
     for i in range(height):
         for j in range(width):
             if chessBoard[i][j] != 0:
                 a = 0 if i - 1 < 0 else chessBoard[i-1][j]
                 b = 0 if i - 1 < 0 and j - 1 < 0 else chessBoard[i-1][j-1]
                 c = 0 if j - 1 < 0 else chessBoard[i][j-1]
                 chessBoard[i][j] = min(a,b,c) + 1
                 k = chessBoard[i][j]
                 while k > 1:
                     nums[k] +=1
                     k-=1                       
    
     #I had to do this weirdness because dictionary operations were killing my time.
     for i, n in enumerate(nums):
         if i >= 2 and n > 0:
             result[i] = n
    
     return result
