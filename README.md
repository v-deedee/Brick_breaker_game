# Brick_breaker_game
Project game cuối kì: Nguyễn Việt Anh - 21020277
# 1. Hướng dẫn cài đặt
Tạo folder muốn cài đặt game, mở bằng Terminal (Visual Studio Code, PowerShell,...), lần lượt nhập các lệnh

`
git clone https://github.com/Nguyen-VietAnh/Brick_breaker_game.git
cd .\Brick_breaker_game\
.\Brick_game.exe
`

# 2. Mô tả
Trò chơi lấy ý tưởng từ game phá gạch cổ điển, người chơi điều khiển thanh trượt bằng chuột đỡ quả bóng đập qua lại để phá vỡ bức tường gạch.

## Luật chơi:
- Khi bắt đầu mỗi màn chơi, người chơi nhấn chuột trái cho quả bóng di chuyển, sau đó di chuyển chuột để điều khiển thanh trượt qua lại trên màn hình đỡ quả bóng để phá vỡ bức tường gạch. Khi quả bóng chạm vào cạnh dưới của màn hình, người chơi sẽ mất một mạng. Khi bắt đầu người chơi sẽ có ba mạng, khi thua cả 3 mạng thì trò chơi kết thúc.

Thanh trượt: ![NewPaddle](https://user-images.githubusercontent.com/100273875/169706560-d7652358-7160-48d3-af20-2f0379f450e5.png)

- Có 3 loại gạch người chơi sẽ gặp:

![GreenBrick](https://user-images.githubusercontent.com/100273875/169706667-e1d33d24-b667-4a98-a1dd-e25ee2c5c48d.png) Gạch xanh lá sẽ biến mất sau một lần bóng đập.


![YellowBrick](https://user-images.githubusercontent.com/100273875/169706689-eb1a81dc-c18b-4a60-ad23-39f7fac3cd6f.png) Gạch vàng sẽ chuyển thành gạch xanh lá sau một lần bóng đập.


![RedBrick](https://user-images.githubusercontent.com/100273875/169706714-e1a8c249-bfe1-4d48-9148-552cf5ccbe34.png) Gạch đỏ sẽ chuyển thành gạch vàng sau một lần bóng đập.





## Minh hoạ

Menu bắt đầu

![pic1](https://user-images.githubusercontent.com/100273875/169706989-98030d83-19e7-4fb6-8ed4-e16cddcfc711.png)



Các màn chơi


![pic2](https://user-images.githubusercontent.com/100273875/169706994-e22babd4-90ac-4bfa-96d6-70bf5e0c304b.png)
![pic3](https://user-images.githubusercontent.com/100273875/169707008-67b072e5-6e4f-4d47-9f5a-eee080116327.png)
![pic4](https://user-images.githubusercontent.com/100273875/169707016-61ad3083-7ec4-4878-acf0-ebca54226e32.png)



Khi người chơi hoàn thành tất cả vòng chơi, menu chiến thắng sẽ xuất hiện


![pic6](https://user-images.githubusercontent.com/100273875/169707040-0bd49fc0-bfbe-465d-a4d8-e044670d50a3.png)


Ngược lại khi người chơi mất hết 3 mạng, menu kết thúc sẽ xuất hiện


![pic5](https://user-images.githubusercontent.com/100273875/169707024-d0e8e16a-449e-4116-88d1-9dc01fc0df90.png)





# 3. Các kỹ thuật sử dụng
- Sử dụng các thư viện đồ hoạ SDL2
- Xử lý va chạm giữa các đối tượng đồ hoạ
- Lập trình hướng đối tượng (Tính đóng gói, kế thừa)
- Xử lý mảng 1 chiều, mảng 2 chiều, vector, cấp phát động, con trỏ,...


# 4. Kết luận
- Hiểu được cách cài đặt một số thư viện đồ hoạ, cách tạo ra, quản lý và vận hành một project.

## Hướng phát triển
- Tạo thêm nhiều level cho game
- Phát triển các tính năng bắn đạn, tăng số lượng bóng, làm thanh trượt dài ra, tăng tốc độ bóng, tăng mạng,...

## Tâm đắc
- Hiểu và áp dụng được phương pháp "chia để trị", tách chương trình thành các file làm những nhiệm vụ riêng biệt để dễ dàng bảo trì và nâng cấp về sau.

# 5. Tham khảo
- http://lazyfoo.net/tutorials/SDL/
- https://phattrienphanmem123az.com/

- Âm thanh: https://mixkit.co/


