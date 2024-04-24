# Linkvideo
[Link video choi game](https://www.youtube.com/watch?v=a8CwpGARAsQ)<br>
# Cách tải game
## Cách 1: Không bao gồm code.
Tải game (được nén thành .zip) tại link sau:<br>
Sau đó giải nén thư mục nhấn vào file overover.exe dể chơi.
[Link tai game](https://github.com/phamtuanviet/game/releases/tag/v1.0.0)<br>
## Cách 2: Bao gồm code và có thể biên dịch.
**Bước 1:** Clone repo này về hoặc Hoặc Chọn Code -> Download Zip.<br>
**Bước 2:** Sau đó giải nén thư mục, chọn bin -> Debug  ->overover.exe để chơi.<br>
# Giới thiệu game
Bạn sẽ điều khiển nhân vật game ![player-idle-4 - Copy](https://github.com/phamtuanviet/game/assets/161930160/35b65c83-9c1a-4705-84a5-bb4f9003fb45)<br>
Né hoặc tiêu diệt các vật cản trong game ![bat-fly1 - Copy](https://github.com/phamtuanviet/game/assets/161930160/44a4daf7-a5ac-4c06-b843-526daf924abd)
![eagle-attack-1 - Copy](https://github.com/phamtuanviet/game/assets/161930160/9b07a407-9c78-4cb8-b5ad-b1680e02cb3a)<br>
Nhân vật sẽ có 3 mạng tối đa ![heart](https://github.com/phamtuanviet/game/assets/161930160/f0a93f84-1d0f-4b75-adc5-8cf7b6981c21)
 <br>
Có 8 năng lượng tối đa ![mana](https://github.com/phamtuanviet/game/assets/161930160/69f6c4bf-16af-4de1-82f6-c82ee0a5c522)
 <br>
Cố gắng sống càng lâu càng tốt.<br>
# Hướng dẫn cách chơi
![tutorial](https://github.com/phamtuanviet/game/assets/161930160/88d26391-5207-4f47-9441-74e4bde996d0)
Bạn điều khiển nhân vật với các nút<br>
A : nhân vật di chuyển sang trái <br>
D : nhân vật di chuyển sang phải <br>
W : nhân vật nhảy lên <br>
S : nhân vật nhảy xuống <br>
Q: nhân vật bắn ra một phi tiêu di chuyển theo đường thẳng ngang màn hình gặp kẻ địch sẽ tiêu diệt chúng.(chiêu này sẽ tiêu tốn một năng lượng) ![Kunai](https://github.com/phamtuanviet/game/assets/161930160/87a98cd5-4afe-4da4-9358-9c035669f454)
<br>
F: nếu dưới chân nhân vật là đất ![dat](https://github.com/phamtuanviet/game/assets/161930160/ec1664b8-d17d-4897-b236-d7fc45723bf7) nhân vật sẽ chèo xuống. <br>
E: nếu trên đầu nhân vật là đất ![dat](https://github.com/phamtuanviet/game/assets/161930160/ec1664b8-d17d-4897-b236-d7fc45723bf7) nhân vật sẽ chèo lên. <br>
R: nhân vật sẽ bắn ra một chuỗi lửa toàn màn hình từ dưới đi lên gặp địch sẽ tiêu diệt chúng.(chiêu này sẽ tiêu tốn 6 năng lượng)![Muzzleflash1](https://github.com/phamtuanviet/game/assets/161930160/7196725e-7c8f-407c-870d-b48bfd9670e5) <br>
# Các vật phẩm khi chơi
Quả cherry ![cherry-1](https://github.com/phamtuanviet/game/assets/161930160/2c517b31-6a10-4119-9315-d3e4dad1df35)
 và bình thuốc ![drug](https://github.com/phamtuanviet/game/assets/161930160/ed2ead7f-6a6d-4fe9-ab0d-de3adaa7d680)
 sẽ hiện ra ngẫu nhiên trên màn hình chơi <br>
 Khi bạn ăn quả cherry sẽ được tăng 1 mạng và 2 năng lượng.<br>
 Khi bạn nhận được thuốc sẽ có một vòng bảo vệ bạn ![khien](https://github.com/phamtuanviet/game/assets/161930160/04f51383-bc53-46bc-b90d-6f301ee34f86) trong 3 giây <br>
# Cơ chế tính điểm và mạng
Khi ![bat-fly1 - Copy](https://github.com/phamtuanviet/game/assets/161930160/44a4daf7-a5ac-4c06-b843-526daf924abd) bay hết màn hình bạn được 1 điểm.<br>
Khi ![bat-fly1 - Copy](https://github.com/phamtuanviet/game/assets/161930160/44a4daf7-a5ac-4c06-b843-526daf924abd) bị tiêu diêt bạn được 3 điểm.<br>
Khi ![eagle-attack-1 - Copy](https://github.com/phamtuanviet/game/assets/161930160/9b07a407-9c78-4cb8-b5ad-b1680e02cb3a) bay hết màn hình bạn được 2 điểm.<br>
Khi ![eagle-attack-1 - Copy](https://github.com/phamtuanviet/game/assets/161930160/9b07a407-9c78-4cb8-b5ad-b1680e02cb3a) bị tiêu diêt bạn được 5 điểm.<br>
Khi bạn bị và chạm thì sẽ mất một mạng khi hết mạng bạn sẽ thua.
# Mô tả hình ảnh và âm thanh
Được lấy từ trên của hàng assetstore (free) <br>
# Mô tả về source code game.
Folder anh : chứa tất cả các ảnh làm game.<br>
Folder nhac : chưa tất cả âm thanh có trong game.<br>
Folder bin : trong đó có file exe để chơi game.
File và Folder SDL2... chứa thư viện để cài đăt SDL2. <br>
File chu.ttf : là phông chữ trong game. <br>
File overover.cbp : là file project trong Codeblocks.<br>
File highscore.txt : để lưu điểm số cao nhất của người chơi.<br>
File .cpp và .h : là file code để hoạt động game. <br>
File readme.md : là file mô tả dự án game. <br>
Những file còn lại : là phần chạy biên dịch trong dự án của codeblocks. <br>
**Game được lấy cảm hừng từ kênh youtube (https://www.youtube.com/@PhatTrienPhanMem123AZ)** <br>
# Mô tả kĩ hơn về các file cpp và h
main.cpp hàm main để khởi tạo và chạy chương trình <br>
Commonfuntion.h và Commonfuntion.cpp bao gồm những hàm và khái niệm chung của cả chương trình.<br>
Baseobject.h và Baseobject.cpp thư viện và chung của nhân vật cơ bản.<br>
Menu.h và Menu.cpp menu của chương trình game và nhưng màn hình khác (pausegame,highscore,tutorial,displayscore).<br>
Enemy.h vầ Enemy.cpp tạo kẻ thù cho game.<br>
Mainobject.h và Mainbject.cpp tạo nhân vật điều khiển.<br>
Bar.h và Bar.cpp tạo thanh máu , năng lượng.<br>
Mapp.h và Mapp.cpp tạo map cho game.<br>
Text.h và Text.cpp tạo chữ hiển thị cho game.<br>
Shoot.h và Shoot.cpp tạo đạn bắn cho nhân vật.<br>
Time.h và Time.cpp tính thời gian chạy trong game.<br>
