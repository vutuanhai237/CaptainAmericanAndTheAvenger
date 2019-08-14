# Captain American and the Avengers

NES game implements by C++/DirectX 9 

![captain-america-cua-biet-doi-avenger-tap-luyen-nhung-mon-vo-gi](https://user-images.githubusercontent.com/43202025/62993593-36725800-be82-11e9-88ee-a06432d5bd24.jpg)

# 1. Giới thiệu

Captain America and the Avengers là một tựa game được phát triển và phát hành bởi Data East vào năm 1991. Game bao gồm các nhân vật trong biệt đội the Avengers thuộc Marvel Comics với nội dung xoay quanh cuộc phiêu lưu của Captain America / Hawk Eye để tìm kiếm Iron Man - Vision đã bị bắt cóc và đối chọi với Red Skull đang tập hợp một đội quân tay sai với âm mưu thôn tính thế giới. 
Cùng với việc phải chiến đấu với những tay lính đánh thuê và tội phạm, người chơi cũng phải đối mặt với những boss sừng sỏ như Wizard, Ultron, sát thủ Crossbones và cuối cùng là Red Skull.

![reviewcaptainamericaavengersnes-2](https://user-images.githubusercontent.com/43202025/62993710-d4feb900-be82-11e9-98ef-44ecda665a59.jpg)

# 2. Gameplay

Người chơi có thể chọn đóng vai một trong hai thành viên của Avengers: Captain America và Hawkeye. Mỗi nhân vật có thể chiến đấu tay đôi, ăn vật phẩm và sử dụng vũ khí tầm xa (khiên của Captain America hoặc cung tên của Hawkeye). Một Avengers khác là the Wasp sẽ xuất hiện để thông tin cho người chơi mỗi khi chuyển màn.

![SpriteSheetCaptain](https://user-images.githubusercontent.com/43202025/62993666-a2ed5700-be82-11e9-9aff-37ec012114ae.png)

# 3. Phím tắt

 Phím | Chức năng |
|-----|---------|
| <kbd>N</kbd> | Chuyển sang màn kế tiếp |
| <kbd>~</kbd> | Tải lại màn hiện tại | 
| <kbd>H</kbd> | Hồi 8 máu |
| <kbd>Q</kbd> | Chuyển chế độ map (sáng - tối), chỉ trong map Pittsburgh và Boss Charleston |


# 4. Điều khiển

 Phím | Chức năng |
|-----|---------|
| <kbd>←</kbd> | Di chuyển sang trái |
| <kbd>→</kbd> | Di chuyển sang phải | 
| <kbd>↓</kbd> | Ngồi |
| <kbd>↑</kbd> | Đỡ khiên phía trên |
| <kbd>Z</kbd> | Tấn công |
| <kbd>X</kbd> | Nhảy |


# 5. Combo

 Tổ hợp | Chức năng |
|-----|---------|
| <kbd>← ← (trong 0.1s)</kbd> | Lướt sang trái |
| <kbd>→ → (trong 0.1s)</kbd> | Lướt sang phải | 
| <kbd>↓ X</kbd> | Nhảy xuống |
| <kbd>↓ Z</kbd> | Đấm thấp |
| <kbd>Z Z (nhấn giữ)</kbd> | Đấm |
| <kbd>X (nhấn giữ)</kbd> | Xoáy (vô địch) |
| <kbd>X (nhấn giữ) ↓ (nhấn giữ)</kbd> | Hạ khiên |
| <kbd>Z X</kbd> | Đá |

# 6. Map

![Untitled](https://user-images.githubusercontent.com/43202025/62994342-90285180-be85-11e9-9287-fbc579b9aba7.png)

![charleston_map](https://user-images.githubusercontent.com/43202025/62994406-ebf2da80-be85-11e9-8de8-69774d39fcfd.png)

<b>Chaleston<b>

![Untitled](https://user-images.githubusercontent.com/43202025/62994390-c82f9480-be85-11e9-861c-44fc4fe2a319.png)

![charleston_boss_light_map](https://user-images.githubusercontent.com/43202025/62994405-eb5a4400-be85-11e9-8f03-a2f169858f79.png)

<b>Chaleston boss<b>

![Untitled](https://user-images.githubusercontent.com/43202025/62994438-1a70b580-be86-11e9-919a-1dea145cf60f.png)

![pittsburgh_dark_portal_2_map](https://user-images.githubusercontent.com/43202025/62994407-edbc9e00-be85-11e9-9487-c9035df82647.png)

<b>Pittsburgh<b>

![Untitled](https://user-images.githubusercontent.com/43202025/62994447-2eb4b280-be86-11e9-8e98-d504429aa26f.png)

<b>Pittsburgh boss

# 7. Kĩ thuật

- Design pattern: state machine, double state machine, singleton.

- Kĩ thuật lập trình: cờ hiệu luân phiên (giảm tối đa số cờ cần sử dụng), chia phase (quản lý bot), tạo road (quản lý boss), enum, kĩ thuật release, con trỏ ***.

- Quản lý mã nguồn: github, merge tay.

# 8. Tài liệu liên quan

- [17520433_17520096_SE102.J31.pdf](https://github.com/haimeohung/Self_Drivring_Car/files/3499816/17520433_17520096_SE102.J31.pdf)

- https://youtu.be/vn-aJki_Cs0?fbclid=IwAR2iAvs-QYD-CQ_EmglTxB5EgPAhSCfEg5Pe7TYLHcANWkHjqm9pX8wA5Vo
