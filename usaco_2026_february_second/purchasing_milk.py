def main():
    n, q = map(int, input().split())
    original_prices = [0]
    queries = []
    largest_query = 0

    original_prices += list(map(int, input().split()))

    for i in range(0, q, 1):
        temp = int(input())
        queries.append(temp)
        largest_query = max(largest_query, temp)

    for i in range(2, n + 1, 1):
        original_prices[i] = min(original_prices[i], 2 * original_prices[i - 1])

    buckets = []
    costs = []
    current_bucket = 1

    for i in range(1, n + 1, 1):
        buckets.append(current_bucket)
        costs.append(original_prices[i])

        if (current_bucket > largest_query):
            break
        
        current_bucket *= 2
    
    for i in range(0, q, 1):
        current_cost = 0
        needed = queries[i]
        best = float('inf')

        for j in range(len(buckets) - 1, -1, -1):
            use = int(needed / buckets[j])
            current_cost += use * costs[j]
            needed -= use * buckets[j]

            prospect_best = 0
            if needed > 0:
                prospect_best = current_cost + costs[j]
            else:
                prospect_best = current_cost
            
            best = min(best, prospect_best)

        print(best)

if __name__ == "__main__":
    main()