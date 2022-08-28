 from datetime import timedelta
 def race(v1, v2, g):
     if v1 >= v2:
         return None
     t = float(g)/float(v2-v1)
     d = timedelta(hours=t)
     ts = float(d.total_seconds())
     h = ts/3600.
     m = ts%3600./60.
     s = ts%3600.%60.
     return [int(h), int(m), int(s)]   
