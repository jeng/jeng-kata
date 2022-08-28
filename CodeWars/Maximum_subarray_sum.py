 def max_sequence(arr):
     sums = [0] * (len(arr) + 1)
     ai = 0
     best = 0
     positive = False
    
     for i in range(1, len(arr) + 1):
         positive = positive or (arr[ai] >= 0)
         sums[i] = max(sums[i - 1] + arr[ai], arr[ai])
         ai += 1
         if sums[i] > best:
             best = sums[i]
    
     if positive:
         return best
     else:
         return 0