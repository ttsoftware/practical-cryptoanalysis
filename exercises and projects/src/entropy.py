import math

def H(P):
    output = 0
    for p in P:
        output += p * math.log((1/p), 2)
    return output

P = [0.08167, 0.01492, 0.02782, 0.04253, 0.012702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02361, 0.00150, 0.01974, 0.00074]

print 'Entropy of drawing a letter with english frequency: ' + str(H(P))
