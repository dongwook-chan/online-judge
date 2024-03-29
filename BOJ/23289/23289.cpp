#include <iostream>
#include <cstring>
#include <vector>

#define MAX_HOUSE_SIZE 20
#define OOH(r, c) (!(1 <= (r) && (r) <= R && 1 <= (c) && (c) <= C)) // Out Of House

using namespace std;

int R, C, K;
int info[MAX_HOUSE_SIZE + 1][MAX_HOUSE_SIZE + 1];
int W;
struct wall{
    int x, y, t;
};
vector<wall> walls;

// # 1.
enum DIRECTION {NONE, RIGHT, LEFT, UP, DOWN};
int dr[] = {0, 0, 0, -1, 1};
int dc[] = {0, 1, -1, 0, 0};
vector<DIRECTION> heat_dir[5][3] = {
    {{}, {}, {}},
    // 오른쪽(1)
    {{UP, RIGHT}, {RIGHT}, {DOWN, RIGHT}},
    // 왼쪽(2)
    {{UP, LEFT}, {LEFT}, {DOWN, LEFT}},
    // 위쪽(3)
    {{RIGHT, UP}, {UP}, {LEFT, UP}},
    // 아래쪽(4)
    {{RIGHT, DOWN}, {DOWN}, {LEFT, DOWN}}
};
struct diff {
    int dr, dc;
} wall_pose_to_check[5] = {
    {0, 0},
    // 오른쪽(1)
    {0, 0},
    // 왼쪽(2)
    {0, -1},
    // 위쪽(3)
    {0, 0},
    // 아래쪽(4)
    {1, 0},
};
int wall_value_to_check[5] = {-1, 1, 1, 0, 0};
bool check_wall(int r, int c, int dir) {
    int nr = r + wall_pose_to_check[dir].dr;
    int nc = c + wall_pose_to_check[dir].dc;

    bool has_wall = false;
    for(wall w : walls) {
        if(w.x != nr || w.y != nc) continue;
        if(w.t == wall_value_to_check[dir]) has_wall = true;// NOTE: (r, c) 일치한다고 바로 return x (2, 2, 0) (2, 2, 1) 모두 존재 가능
    }
    return has_wall;
}

int heat[MAX_HOUSE_SIZE + 1][MAX_HOUSE_SIZE + 1];
bool visited[MAX_HOUSE_SIZE + 1][MAX_HOUSE_SIZE + 1];
// 그 다음 이 바람은 계속 다른 칸으로 이동해 다른 칸의 온도를 위의 그림과 같이 상승시키게 된다.
// 어떤 칸 (x, y)에 온풍기 바람이 도착해 온도가 k (> 1)만큼 상승했다면, (x-1, y+1), (x, y+1), (x+1, y+1)의 온도도 k-1만큼 상승하게 된다. 
void propagate_heat(int h, int r, int c, int dir) {
    visited[r][c] = true;
    heat[r][c] += h;

    if(h == 1) return;

    for(int i = 0; i < 3; ++ i) {   // 3번 이동
        int nr = r;
        int nc = c;
        for(DIRECTION d : heat_dir[dir][i]) {
            if(check_wall(nr, nc, d)) goto next_move;    // 일부 칸과 칸 사이에는 벽이 있어 온풍기 바람이 지나갈 수 없다.
            nr += dr[d];
            nc += dc[d];
        }
        if(OOH(nr, nc)) continue;   // 이때 그 칸이 존재하지 않는다면, 바람은 이동하지 않는다.
        if(visited[nr][nc]) continue;   // 온풍기에서 바람이 한 번 나왔을 때, 어떤 칸에 같은 온풍기에서 나온 바람이 여러 번 도착한다고 해도 온도는 여러번 상승하지 않는다.

        propagate_heat(h - 1, nr, nc, dir);
    next_move:
        continue;
    }
}

// # 2.
int heat_diff[MAX_HOUSE_SIZE + 1][MAX_HOUSE_SIZE + 1];

// # 3.

// # 4.
int chocolate_ctr;

// # 5.

int main() {
    cin >> R >> C >> K;
    for(int r = 1; r <= R; ++r) {
        for(int c = 1; c <= C; ++c) {
            cin >> info[r][c];
        }
    }
    cin >> W;
    //memset(wall, NO_WALL, sizeof(wall));
    for(int w = 0; w < W; ++w) {
        int x, y, t;
        cin >> x >> y >> t;
        walls.push_back({x, y, t});  // NOTE: wall 배열이 하나면 (2, 2, 0), (2, 2, 1)을 동시에 표현 불가 -> 문제 주어진 input 가공하지 말고 그대로 사용!
    }
    // 구사과의 성능 테스트는 다음과 같은 작업이 순차적으로 이루어지며, 가장 처음에 모든 칸의 온도는 0이다. 문제의 그림에서 빈 칸은 온도가 0인 칸을 의미한다.
    while(true) {
        // # 1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
        for(int info_r = 1; info_r <= R; ++info_r) {
            for(int info_c = 1; info_c <= C; ++info_c) {
                switch(info[info_r][info_c]) {
                    case 0: case 5: // 빈 칸 OR 온도를 조사해야 하는 칸
                        continue;
                }
                // 온풍기에서 바람이 한 번 나왔을 때, 온풍기의 바람이 나오는 방향에 있는 칸은 항상 온도가 5도 올라간다. 
                int dir = info[info_r][info_c];
                int r = info_r + dr[dir];
                int c = info_c + dc[dir];

                memset(visited, false, sizeof(visited));
                propagate_heat(5, r, c, dir);
            }
        }
        // # 2. 온도가 조절됨
        memset(heat_diff, 0, sizeof(heat_diff));
        for(int heat_r = 1; heat_r <= R; ++heat_r) {
            for(int heat_c = 1; heat_c <= C; ++heat_c) {

                for(int dir = 1; dir <= 4; ++dir) {
                    // 인접한 두 칸 사이에 벽이 있는 경우에는 온도가 조절되지 않는다.
                    if(check_wall(heat_r, heat_c, dir)) continue;

                    // 모든 인접한 칸에 대해서,
                    int nr = heat_r + dr[dir];
                    int nc = heat_c + dc[dir];
                    if(OOH(nr, nc)) continue;
                    if(heat[heat_r][heat_c] <= heat[nr][nc]) continue;

                    // 온도가 높은 칸에서 낮은 칸으로 ⌊(두 칸의 온도의 차이)/4⌋만큼 온도가 조절된다.
                    int diff = (heat[heat_r][heat_c] - heat[nr][nc]) / 4;
                    heat_diff[heat_r][heat_c] -= diff;
                    heat_diff[nr][nc] += diff;
                }
            }
        }
        for(int heat_r = 1; heat_r <= R; ++heat_r) {
            for(int heat_c = 1; heat_c <= C; ++heat_c) {
                heat[heat_r][heat_c] += heat_diff[heat_r][heat_c];
            }
        }
        // # 3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
        if(heat[1][1]) --heat[1][1];    // NOTE: 모서리 중복 처리하지 않도록 주의!
        if(heat[1][C]) --heat[1][C];
        if(heat[R][1]) --heat[R][1];
        if(heat[R][C]) --heat[R][C];
        for(int heat_c = 2; heat_c < C; ++heat_c) {   
            if(heat[1][heat_c]) --heat[1][heat_c];
            if(heat[R][heat_c]) --heat[R][heat_c];
        }
        for(int heat_r = 2; heat_r < R; ++heat_r) {   
            if(heat[heat_r][1]) --heat[heat_r][1];
            if(heat[heat_r][C]) --heat[heat_r][C];
        }
        // # 4. 초콜릿을 하나 먹는다.
        ++chocolate_ctr;
        if(chocolate_ctr > 100) break;

        // # 5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사. 모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
        for(int info_r = 1; info_r <= R; ++info_r) {
            for(int info_c = 1; info_c <= C; ++info_c) {
                if(info[info_r][info_c] < 5) continue;
                if(heat[info_r][info_c] < K) goto next_test;
            }
        }
        break;
    next_test:
        continue;
    }

    cout << chocolate_ctr;
    return 0;
}