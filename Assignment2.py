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

def prim(dist): #make mst
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

def find_odd_degree(mst, n): #find vertex with odd degree
    degree = [0] * n
    odd_vertices = []

    for u, v in mst:
        degree[u] += 1
        degree[v] += 1

    for i in range(n):
        if degree[i] % 2 == 1:
            odd_vertices.append(i)

    return odd_vertices

def greedy_matching(odd_vertices, dist): #find perfect matching through greedy
    unmatched = odd_vertices[:]
    result = []

    while unmatched:
        u = unmatched[0]
        min_dist = float('inf')
        min_v = -1

        for i in range(1, len(unmatched)):
            v = unmatched[i]
            if dist[u][v] < min_dist:
                min_dist = dist[u][v]
                min_v = v

        result.append((u, min_v))
        unmatched.remove(u)
        unmatched.remove(min_v)

    return result

def build_multigraph(mst_edges, matching_edges): #euler
    graph = {}
    for u, v in mst_edges + matching_edges:
        if u not in graph:
            graph[u] = []
        if v not in graph:
            graph[v] = []
        graph[u].append(v)
        graph[v].append(u)
    return graph

def find_eulerian_circuit(graph):
    circuit = []
    stack = []

    for node in graph:
        if graph[node]:
            stack.append(node)
            break

    while stack:
        u = stack[-1]
        if graph[u]:
            v = graph[u].pop()
            graph[v].remove(u)
            stack.append(v)
        else:
            circuit.append(stack.pop())

    return circuit[::-1]

def euler_to_tsp_path(euler_circuit): #hamilton
    max_index = max(euler_circuit)
    visited = [False] * (max_index + 1)
    tsp_path = []

    for node in euler_circuit:
        if not visited[node]:
            visited[node] = True
            tsp_path.append(node)

    tsp_path.append(tsp_path[0])
    return tsp_path


def calculate_tour_length(path, dist_matrix): #length calculate
    total = 0
    for i in range(1, len(path)):
        total += dist_matrix[path[i-1]][path[i]]
    return total



# test
dist_matrix = parse_tsp_file("xql662.tsp")

mst = prim(dist_matrix)

odd_vertices = find_odd_degree(mst, len(dist_matrix))

matching = greedy_matching(odd_vertices, dist_matrix)

multigraph = build_multigraph(mst, matching)

euler_circuit = find_eulerian_circuit(multigraph)

tsp_path = euler_to_tsp_path(euler_circuit)
print("TSP Path:", tsp_path)

tour_length = calculate_tour_length(tsp_path, dist_matrix)
print("Total Tour Length:", tour_length)
