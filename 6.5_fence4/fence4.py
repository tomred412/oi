'''
ID: dermotl1
LANG: PYTHON3
PROG: fence4
'''

from dataclasses import dataclass
from functools import cmp_to_key
import math

@dataclass
class point:
    x: float
    y: float

@dataclass
class segment:
    p1: point
    p2: point
    pos1: int
    pos2: int
    segment_id: int

def getToken():
    for i in open("fence4.in", "r"):
        for j in i.split():
            yield j

token = getToken()

def fin():
    return next(token)

def isBetween(test, a, b):
    return test >= min(a, b) - 1e-9 and test <= max(a, b) + 1e-9

def isPointOnSegment(p, s):
    return isBetween(p.x, s.p1.x, s.p2.x) and isBetween(p.y, s.p1.y, s.p2.y)

def isEndpoint(p, s):
    d1 = math.sqrt((p.x - s.p1.x)**2 + (p.y - s.p1.y)**2)
    d2 = math.sqrt((p.x - s.p2.x)**2 + (p.y - s.p2.y)**2)
    return d1 < 1e-9 or d2 < 1e-9

def doesIntersection(s1, s2, check_fence):
    is_vertical1 = abs(s1.p1.x - s1.p2.x) < 1e-9
    is_vertical2 = abs(s2.p1.x - s2.p2.x) < 1e-9

    if is_vertical1 and is_vertical2:
        return False
    
    elif is_vertical1:
        x_intersect = s1.p1.x
        slope2 = (s2.p2.y - s2.p1.y) / (s2.p2.x - s2.p1.x)
        b2 = s2.p1.y - slope2 * s2.p1.x
        y_intersect = slope2 * x_intersect + b2

    elif is_vertical2:
        x_intersect = s2.p1.x
        slope1 = (s1.p2.y - s1.p1.y) / (s1.p2.x - s1.p1.x)
        b1 = s1.p1.y - slope1 * s1.p1.x
        y_intersect = slope1 * x_intersect + b1

    else:
        slope1 = (s1.p2.y - s1.p1.y) / (s1.p2.x - s1.p1.x)
        b1 = s1.p1.y - slope1 * s1.p1.x
        slope2 = (s2.p2.y - s2.p1.y) / (s2.p2.x - s2.p1.x)
        b2 = s2.p1.y - slope2 * s2.p1.x

        if abs(slope1 - slope2) < 1e-9:
            return False
        
        x_intersect = (b2 - b1) / (slope1 - slope2)
        y_intersect = slope1 * x_intersect + b1
    
    intersection = point(x_intersect, y_intersect)

    if isPointOnSegment(intersection, s1) and isPointOnSegment(intersection, s2):
        if check_fence:
            if isEndpoint(intersection, s1) or isEndpoint(intersection, s2):
                return False
        return True
    
    return False

def calculateIntersection(s1, s2):
    is_vertical1 = abs(s1.p1.x - s1.p2.x) < 1e-9
    is_vertical2 = abs(s2.p1.x - s2.p2.x) < 1e-9

    if is_vertical1:
        x_intersect = s1.p1.x
        slope2 = (s2.p2.y - s2.p1.y) / (s2.p2.x - s2.p1.x)
        b2 = s2.p1.y - slope2 * s2.p1.x
        y_intersect = slope2 * x_intersect + b2

    elif is_vertical2:
        x_intersect = s2.p1.x
        slope1 = (s1.p2.y - s1.p1.y) / (s1.p2.x - s1.p1.x)
        b1 = s1.p1.y - slope1 * s1.p1.x
        y_intersect = slope1 * x_intersect + b1

    else:
        slope1 = (s1.p2.y - s1.p1.y) / (s1.p2.x - s1.p1.x)
        b1 = s1.p1.y - slope1 * s1.p1.x
        slope2 = (s2.p2.y - s2.p1.y) / (s2.p2.x - s2.p1.x)
        b2 = s2.p1.y - slope2 * s2.p1.x
        
        x_intersect = (b2 - b1) / (slope1 - slope2)
        y_intersect = slope1 * x_intersect + b1
    
    answer = point(x_intersect, y_intersect)
    return answer

def isUpperHalf(p, observer):
    if p.y > observer.y:
        return True
    if p.y < observer.y:
        return False
    return p.x > observer.x

def compare_points(a, b, observer):
    upper_a = isUpperHalf(a, observer)
    upper_b = isUpperHalf(b, observer)

    if upper_a != upper_b:
        return -1 if upper_a else 1
    
    dx1 = a.x - observer.x
    dy1 = a.y - observer.y
    dx2 = b.x - observer.x
    dy2 = b.y - observer.y

    return -1 if (dx1 * dy2 - dy1 * dx2) > 0 else 1

def main():
    fout = open("fence4.out", "w")

    n = int(fin())
    observer = point(float(fin()), float(fin()))

    corners = []
    for i in range(n):
        corners.append(point(float(fin()), float(fin())))

    fences = []
    for i in range(n):
        next = (i + 1) % n
        fences.append(segment(corners[i], corners[next], i + 1, next + 1, i))
    
    for i in range(n):
        for j in range(i + 2, n):
            if i == 0 and j == n - 1:
                continue
            if doesIntersection(fences[i], fences[j], True):
                fout.write("NOFENCE\n")
                return
            
    is_fence_visible = [False] * n
    sorted_corners = sorted(corners, key=cmp_to_key(lambda a, b: compare_points(a, b, observer)))

    for i in range(len(sorted_corners)):
        p1 = sorted_corners[i]
        p2 = sorted_corners[(i + 1) % len(sorted_corners)]

        if (abs((p1.x - observer.x) * (p2.y - observer.y) - (p1.y - observer.y) * (p2.x - observer.x)) < 1e-9) and (((p1.x - observer.x) * (p2.x - observer.x) + (p1.y - observer.y) * (p2.y - observer.y)) > 0):
            continue

        mid_dx = (p1.x - observer.x) + (p2.x - observer.x)
        mid_dy = (p1.y - observer.y) + (p2.y - observer.y)

        ray = segment(observer, point(observer.x + mid_dx * 200000, observer.y + mid_dy * 200000), -1, -1, -1)\
        
        min_dist = float('inf')
        closest_id = -1
        
        for j in range(n):
            if doesIntersection(ray, fences[j], False):
                hit = calculateIntersection(ray, fences[j])
                dist = math.hypot(hit.x - observer.x, hit.y - observer.y)

                if dist < min_dist:
                    min_dist = dist
                    closest_id = j
        
        if closest_id != -1: is_fence_visible[closest_id] = True

    output = []
    for i in range(n):
        if is_fence_visible[i]:
            out = fences[i]
            if out.pos1 > out.pos2:
                out.pos1, out.pos2 = out.pos2, out.pos1
                out.p1, out.p2 = out.p2, out.p1
            output.append(out)

    output.sort(key=lambda x: (x.pos2, x.pos1))

    fout.write(f"{len(output)}\n")

    for it in output:
        fout.write(f"{int(it.p1.x)} {int(it.p1.y)} {int(it.p2.x)} {int(it.p2.y)}\n")

    fout.close()

if __name__ == "__main__":
    main()

