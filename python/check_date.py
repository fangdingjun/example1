#!/usr/bin/env python

def check_date(d):
    dl=d.split("-")
    try:
        if len(dl[0]) != 4:
            return False
        elif int(dl[0]) < 0:
            return False
        d1=int(dl[0])
        d2=int(dl[1])
        if d2 > 12 or d2 < 0:
            return False
        d3=int(dl[2])
        if d3 > 31 or d3 < 0:
            return False
        if d2 in [4,6,9,11]:
            if d3 > 30:
                return False
        if d2 == 2:
            if (d1 % 4) == 0 or (d1 % 400) == 0:
                if d3 > 29:
                    return False
            else:
                if d3 > 28:
                    return False
    except:
        return False
    return True

if __name__ == "__main__":
    if check_date("1999-13-30"):
        print "ok"
    else:
        print "not ok"

