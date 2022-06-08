# Brick_breaker_game
Project game cuối kì: Nguyễn Việt Anh - 21020277
# 1. Hướng dẫn cài đặt
Tạo folder muốn cài đặt game, mở bằng Terminal (Visual Studio Code, PowerShell,...), lần lượt nhập các lệnh:

`git clone https://github.com/Nguyen-VietAnh/Brick_breaker_game.git`

`cd .\Brick_breaker_game\`

`.\Brick_game.exe`


# 2. Mô tả
Trò chơi lấy ý tưởng từ game phá gạch cổ điển, người chơi điều khiển thanh trượt đỡ quả bóng đập qua lại để phá vỡ bức tường gạch.

- Video demo: https://youtu.be/PmVA2-DIvhI

## Luật chơi:
- Khi bắt đầu mỗi màn chơi, người chơi nhấn chuột trái cho quả bóng di chuyển, sau đó di chuyển chuột để điều khiển thanh trượt qua lại trên màn hình đỡ quả bóng để phá vỡ bức tường gạch. Khi quả bóng chạm vào cạnh dưới của màn hình, người chơi sẽ mất một mạng. Khi bắt đầu người chơi sẽ có ba mạng, khi thua cả 3 mạng thì trò chơi kết thúc.

Thanh trượt: ![NewPaddle](https://user-images.githubusercontent.com/100273875/169706560-d7652358-7160-48d3-af20-2f0379f450e5.png)

- Có 4 loại gạch người chơi sẽ gặp:

![GreenBrick](https://user-images.githubusercontent.com/100273875/169706667-e1d33d24-b667-4a98-a1dd-e25ee2c5c48d.png) Gạch xanh lá sẽ biến mất sau một lần bóng đập.


![YellowBrick](https://user-images.githubusercontent.com/100273875/169706689-eb1a81dc-c18b-4a60-ad23-39f7fac3cd6f.png) Gạch vàng sẽ chuyển thành gạch xanh lá sau một lần bóng đập.


![RedBrick](https://user-images.githubusercontent.com/100273875/169706714-e1a8c249-bfe1-4d48-9148-552cf5ccbe34.png) Gạch đỏ sẽ chuyển thành gạch vàng sau một lần bóng đập.


![PlatinumBrick](https://user-images.githubusercontent.com/100273875/171680180-bf2dd5c2-882e-45d2-bff3-6d7f91302a70.png) Gạch xám không thể bị phá vỡ.




- Khi phá vỡ một số viên gạch nhất định sẽ xuất hiện ngẫu nhiên các items. Có tất cả 5 loại item:

![Gun_item](https://user-images.githubusercontent.com/100273875/171681253-6c53dcfd-b251-4762-8372-50cb82c97e7f.png)    Gun item: tạo loạt đạn từ thanh trượt giúp phá vỡ bức tường gạch nhanh hơn.


![Multi_ball_item](https://user-images.githubusercontent.com/100273875/171681303-0e28e276-1163-40d7-b6b5-786c7cf8829e.png)    Multi ball item: tạo ra 3 quả bóng


![Long_item](https://user-images.githubusercontent.com/100273875/171681455-a1a9a967-72e4-43ad-9c3d-87695f6cb60b.png)    Long item: kéo dài thanh trượt


![Short_item](https://user-images.githubusercontent.com/100273875/171681532-cbc53350-7658-4da3-b0bb-23e9693d3efc.png)    Short item: làm ngắn thanh trượt


![Speed_up_item](https://user-images.githubusercontent.com/100273875/171681605-a215e425-be46-4b83-91d9-180ad3cf2b9c.png)    Speed up item: tăng tốc độ bóng




## Minh hoạ

- Menu bắt đầu:

![Main_menu](https://user-images.githubusercontent.com/100273875/171682490-ab575866-8dce-49fc-b0f6-c89397cd332f.png)




- Game play:

![Main_play](https://user-images.githubusercontent.com/100273875/171682012-61e617c4-833b-4609-a4c8-e3a99b6d416d.png)




- Các màn chơi:


![level3](https://user-images.githubusercontent.com/100273875/171684796-35102e20-295c-463e-bb6b-ec1c3d4218e6.png)
![level4](https://user-images.githubusercontent.com/100273875/171684873-3391ec43-a877-4724-b90f-a92ba62c5001.png)
![level5](https://user-images.githubusercontent.com/100273875/171684883-e4f53e4c-3c7f-4545-96a4-1615548f3fe2.png)
![level6 1](https://user-images.githubusercontent.com/100273875/171684897-874cbefa-be28-44af-ba27-1a0082972a6b.png)
![level7](https://user-images.githubusercontent.com/100273875/171684905-6ecf08b1-dce7-48e1-ba05-7fdf5f2f91ab.png)
![level8](https://user-images.githubusercontent.com/100273875/171684920-982adec7-2b55-42a8-a49a-c741280e9857.png)




- Khi người chơi hoàn thành tất cả vòng chơi, menu chiến thắng sẽ xuất hiện:


![win_game](https://user-images.githubusercontent.com/100273875/171684956-2a9e2321-f376-44eb-93a0-0ee770662e5f.png)



- Ngược lại khi người chơi mất hết 3 mạng, menu kết thúc sẽ xuất hiện:


![game_over](https://user-images.githubusercontent.com/100273875/171685006-85cc249e-479b-46bd-a5d3-0a9230485f45.png)






# 3. Các kỹ thuật sử dụng
- Sử dụng các thư viện đồ hoạ SDL2.
- Xử lý va chạm giữa các đối tượng đồ hoạ.
- Lập trình hướng đối tượng (Tính đóng gói, kế thừa).
- Xử lý mảng 1 chiều, mảng 2 chiều, vector, cấp phát động, con trỏ,...
- Nhập xuất với tệp văn bản.


# 4. Kết luận
- Hiểu được cách cài đặt một số thư viện đồ hoạ, cách tạo ra, quản lý và vận hành một project.

## Hướng phát triển
- Hoàn thiện các tính năng đã có: thêm nhạc nền, thêm menu dừng tạm thời, menu cài đặt, giới thiệu...
- Tạo thêm nhiều level cho game.
- Thêm nhiều chế độ chơi: Time attack, Insane, Endless,..

## Tâm đắc
- Hiểu và áp dụng được phương pháp "chia để trị", tách chương trình thành các file làm những nhiệm vụ riêng biệt để dễ dàng bảo trì và nâng cấp về sau.

# 5. Tham khảo
- http://lazyfoo.net/tutorials/SDL/
- https://phattrienphanmem123az.com/

- Âm thanh: https://mixkit.co/


