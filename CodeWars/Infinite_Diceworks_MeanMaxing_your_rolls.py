 def mean_max(faces, rolls):
     powers = [0] * (faces + 1)
     means = [0] * (faces + 1)
     single = 0
     for i in range(1, faces + 1):
         powers[i] = i ** rolls
         means[i] = means[i-1] + (i * (powers[i] - powers[i-1]))
         single += i
     return (means[faces]/powers[faces]) - (single/faces)
