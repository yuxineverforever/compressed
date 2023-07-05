<h1 align="center">Distributed Butterfly Counting for Large-scale Bipartite Graph</h1>

**Format of Bipartite Graph:**
```
number of nodes in the left side

number  of nodes in the right side

edges
```

*Monarch* vs *BFC-IBS*:
- if graph is more sparse, Monarch is faster.
- if graph is more dense, BFC-IBS is faster.


```
size of the hash map: 40713
Time of neighbor searching: 0.0106994 secs.
Time of aggregation: 0.000502765 secs.
Loop Count : 40713
0
Time of monarch: 0.0153243 secs.
```
```
size of the hash map: 40713
Time of neighbor searching: 0.0155628 secs.
Time of aggregation: 0.000988851 secs.
Loop Count : 151425
0
Time of BFC_IBS: 0.0237132 secs.
```
```
size of the hash map: 32314
Time of neighbor searching: 0.0365774 secs.
Time of aggregation: 0.00209605 secs.
Loop Count : 32314
0
Time of BFC_VPS: 0.0419738 secs.
```
```
size of the hash map: 40622
Time of neighbor searching: 0.00746102 secs.
Time of aggregation: 0.000263345 secs.
Loop Count : 40625
3
Time of monarch: 0.0119521 secs.
```
```
size of the hash map: 40622
Time of neighbor searching: 0.0118565 secs.
Time of aggregation: 0.000982443 secs.
Loop Count : 151249
3
Time of BFC_IBS: 0.0192988 secs.
```
```
size of the hash map: 32161
Time of neighbor searching: 0.0270899 secs.
Time of aggregation: 0.00196164 secs.
Loop Count : 32164
3
Time of BFC_VPS: 0.0321736 secs.
```
