import math
from itertools import permutations
import time

def calculate_distances():
    """주어진 좌표의 거리 행렬 계산"""
    coords = [
        (18, 15),   # 도시 0 (시작점)
        (29, 20),   # 도시 1
        (46, 28),   # 도시 2
        (47, 31),   # 도시 3
        (53, 43),   # 도시 4
        (73, 55),   # 도시 5
        (76, 57),   # 도시 6
        (79, 59),   # 도시 7
        (90, 62),   # 도시 8
        (97, 72)    # 도시 9
    ]
    
    n = len(coords)
    dist = [[0.0] * n for _ in range(n)]
    
    for i in range(n):
        for j in range(n):
            if i != j:
                dx = coords[i][0] - coords[j][0]
                dy = coords[i][1] - coords[j][1]
                dist[i][j] = math.sqrt(dx**2 + dy**2)
    
    return dist, coords

def brute_force_tsp_detailed(dist):
    """완전 탐색으로 TSP 해결 - 상세 정보 포함"""
    n = len(dist)
    cities = list(range(1, n))  # 도시 0에서 시작하므로 1~9만 순열
    
    min_cost = float('inf')
    best_path = None
    total_permutations = math.factorial(n-1)
    
    print(f"완전 탐색 시작: {total_permutations:,}가지 경우 확인")
    start_time = time.time()
    
    count = 0
    for perm in permutations(cities):
        # 경로: 0 -> perm[0] -> perm[1] -> ... -> perm[8] -> 0
        path = [0] + list(perm) + [0]
        cost = 0
        
        # 경로 비용 계산
        for i in range(len(path) - 1):
            cost += dist[path[i]][path[i+1]]
        
        if cost < min_cost:
            min_cost = cost
            best_path = path[:-1]  # 마지막 0 제거 (순환이므로)
        
        count += 1
        if count % 50000 == 0:
            progress = count / total_permutations * 100
            print(f"진행률: {progress:.1f}% ({count:,}/{total_permutations:,})")
    
    end_time = time.time()
    print(f"완전 탐색 완료! 소요 시간: {end_time - start_time:.2f}초")
    
    return min_cost, best_path

def verify_path_cost(dist, path):
    """주어진 경로의 비용 계산 및 검증"""
    total_cost = 0
    print(f"\n경로 검증: {' -> '.join(map(str, path))} -> {path[0]}")
    print("구간별 거리:")
    
    for i in range(len(path)):
        from_city = path[i]
        to_city = path[(i + 1) % len(path)]  # 순환
        segment_cost = dist[from_city][to_city]
        total_cost += segment_cost
        print(f"  도시 {from_city} -> 도시 {to_city}: {segment_cost:.2f}")
    
    print(f"총 비용: {total_cost:.2f}")
    return total_cost

def show_coordinates_and_distances():
    """좌표와 주요 거리 정보 표시"""
    dist, coords = calculate_distances()
    
    print("=== 도시 좌표 ===")
    for i, (x, y) in enumerate(coords):
        print(f"도시 {i}: ({x}, {y})")
    
    print("\n=== 인접 도시간 거리 (참고용) ===")
    # 몇 가지 주요 거리만 표시
    key_pairs = [(0,1), (1,2), (2,3), (3,4), (4,5), (5,6), (6,7), (7,8), (8,9), (9,0)]
    for i, j in key_pairs:
        print(f"도시 {i} <-> 도시 {j}: {dist[i][j]:.2f}")
    
    return dist, coords

def check_result_196_81():
    """196.81이 정답인지 확인"""
    print("=== TSP small1 데이터셋 검산 ===")
    
    dist, coords = show_coordinates_and_distances()
    
    print(f"\n보고된 결과: 196.81")
    print("완전 탐색으로 검증 중...")
    
    try:
        min_cost, best_path = brute_force_tsp_detailed(dist)
        print(f"\n✓ 최적 해: {min_cost:.2f}")
        print(f"✓ 최적 경로: {best_path}")
        
        # 경로 비용 상세 검증
        verified_cost = verify_path_cost(dist, best_path)
        
        # 결과 비교
        if abs(min_cost - 196.81) < 0.01:
            print(f"\n🎉 검산 결과: 196.81이 정답입니다!")
        else:
            print(f"\n❌ 불일치: 실제 최적해는 {min_cost:.2f}입니다.")
            
        return min_cost, best_path
        
    except KeyboardInterrupt:
        print("\n계산이 중단되었습니다.")
        return None, None

# 빠른 검증을 위한 샘플링 방법
def quick_verification_sampling(dist, target_cost=196.81, sample_size=100000):
    """샘플링을 통한 빠른 검증"""
    import random
    
    n = len(dist)
    cities = list(range(1, n))
    
    print(f"\n빠른 검증: {sample_size:,}개 랜덤 경로 샘플링")
    
    min_found = float('inf')
    best_path_found = None
    better_count = 0
    
    for _ in range(sample_size):
        # 랜덤 순열 생성
        random.shuffle(cities)
        path = [0] + cities
        
        # 비용 계산
        cost = sum(dist[path[i]][path[(i+1) % len(path)]] for i in range(len(path)))
        
        if cost < min_found:
            min_found = cost
            best_path_found = path
            
        if cost < target_cost:
            better_count += 1
    
    print(f"샘플링 결과:")
    print(f"  - 발견된 최소 비용: {min_found:.2f}")
    print(f"  - 196.81보다 좋은 해: {better_count}개")
    
    if better_count > 0:
        print(f"  ⚠️  196.81보다 좋은 해가 발견되었습니다!")
    else:
        print(f"  ✓ 196.81이 매우 좋은 해로 보입니다.")
    
    return min_found, best_path_found

# 실행
if __name__ == "__main__":
    # 먼저 빠른 샘플링으로 검증
    dist, coords = calculate_distances()
    quick_min, quick_path = quick_verification_sampling(dist)
    
    # 사용자 선택
    print(f"\n완전 탐색을 실행하시겠습니까? (약 1-2분 소요)")
    print("y: 완전 탐색 실행")
    print("n: 샘플링 결과만 확인")
    
    choice = input("선택 (y/n): ").strip().lower()
    
    if choice == 'y':
        check_result_196_81()
    else:
        print(f"\n샘플링 기준 검증 완료:")
        print(f"발견된 최소 비용: {quick_min:.2f}")