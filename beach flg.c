#include <stdio.h>
#include <stdbool.h>

// 擬似関数群（ハード依存の部分は各自実装）
void init_all();
bool is_start_button_pressed();
int get_bottle_position();  // -100(左) ～ +100(右)、0なら中心
void rotate_left();
void rotate_right();
void move_forward();
void stop_motor();
bool detect_collision();  // タッチ or 超音波センサ
void play_success_sound();

int main() {
    // 初期化
    init_all();
    printf("ロボット初期化完了。スタート待機中...\n");

    // スタートボタンが押されるまで待機
    while (!is_start_button_pressed()) {
        // 何もしない
    }

    printf("スタート！探索開始。\n");

    while (1) {
        int position = get_bottle_position();  // カメラによるボトルの位置取得

        // 画面中央に来るまで回転
        if (position < -10) {
            rotate_left();
            printf("左旋回中（位置: %d）\n", position);
        } else if (position > 10) {
            rotate_right();
            printf("右旋回中（位置: %d）\n", position);
        } else {
            // ほぼ中心に来たら前進
            move_forward();
            printf("前進中！\n");
        }

        // 衝突検知（タッチセンサまたは超音波）
        if (detect_collision()) {
            stop_motor();
            printf("衝突検知！停止します。\n");
            break;
        }
    }

    // 終了処理
    play_success_sound();
    printf("ボトル取得完了！\n");

    return 0;
}
