def parse_tsp_file(filepath): #parsing tsp file to dist_matrix
    with open(filepath, 'r') as f:
        lines = f.readlines()

    coords = []
    dimension = 0
    reading_coords = False

    for line in lines:
        line = line.strip()
        if line.startswith("DIMENSION"):
            dimension = int(line.split(":")[1])
        elif line.startswith("NODE_COORD_SECTION"):
            reading_coords = True
            continue
        elif line == "EOF":
            break
        elif reading_coords:
            parts = line.split()
            if len(parts) >= 3:
                x, y = float(parts[1]), float(parts[2])
                coords.append((x, y))

    dist = [[0.0] * dimension for _ in range(dimension)]
    for i in range(dimension):
        for j in range(dimension):
            if i != j:
                dx = coords[i][0] - coords[j][0]
                dy = coords[i][1] - coords[j][1]
                dist[i][j] = round((dx**2 + dy**2)**0.5, 2)

    return dist

def held_karp(dist):
    min_distance = float('inf')
    n = len(dist)
    DP = [[float('inf')] * n for _ in range(2**n)]
    DP[1][0] = 0 
    for subset_mask in range(2 ** n):
        if not (subset_mask & 1):
            continue 
        for j in range(n):
            if not (subset_mask >> j) & 1 or j == 0: continue
            prev_mask = subset_mask ^ (1 << j)
            for k in range(n):
                if not (prev_mask >> k) & 1: 
                    continue
                DP[subset_mask][j] = min(DP[subset_mask][j], DP[prev_mask][k] + dist[k][j])
    full_mask = 2 ** n - 1
    for j in range(1, n):
        min_distance = min(min_distance, DP[full_mask][j] + dist[j][0])

    return min_distance

def prim(dist):
    n = len(dist)
    in_mst = [False] * n
    min_edge = [float('inf')] * n
    min_edge[0] = 0
    parent = [-1] * n
    mst_edges = []

    for i in range(n):
        u = -1
        min_cost = float('inf')
        for v in range(n):
            if not in_mst[v] and min_edge[v] < min_cost:
                min_cost = min_edge[v]
                u = v

        if u == -1:
            break

        in_mst[u] = True

        if parent[u] != -1:
            mst_edges.append((parent[u], u))

        for v in range(n):
            if not in_mst[v] and dist[u][v] < min_edge[v]:
                min_edge[v] = dist[u][v]
                parent[v] = u

    return mst_edges



dist_matrix = parse_tsp_file("a280.tsp")
mst = prim(dist_matrix)
print(mst)