import math

def circle_intersection_area(r1, r2, d):
    """
    Calculate the area of the intersection of two circles.

    Parameters:
    - r1: Radius of the first circle.
    - r2: Radius of the second circle.
    - d: Distance between the centers of the two circles.

    Returns:
    - The area of the intersection of the two circles.
    """
    if d >= r1 + r2:  # Disjoint circles
        return 0
    elif d <= abs(r1 - r2):  # One circle is contained in the other
        return math.pi * min(r1, r2)**2
    else:  # Partially overlapping circles
        # Compute the intersection area
        part1 = r1**2 * math.acos((d**2 + r1**2 - r2**2) / (2 * d * r1))
        part2 = r2**2 * math.acos((d**2 + r2**2 - r1**2) / (2 * d * r2))
        part3 = 0.5 * math.sqrt((-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2))
        
        return part1 + part2 - part3