# Kiến trúc CISC và RISC trong hệ thống máy tính

## 1.1 Khái niệm cơ bản về CISC và RISC

**CISC (Complex Instruction Set Computer)** là kiến trúc máy tính được thiết kế để hỗ trợ các lệnh phức tạp, mỗi lệnh có thể thực hiện nhiều bước thao tác thấp cấp (load, tính toán, lưu trữ) trong một lần thực thi. Nhờ đó, một lệnh CISC có thể biểu diễn một phép toán cao hơn hoặc một loạt phép toán ở mức ngôn ngữ cấp cao, giúp mã máy ngắn hơn và bộ biên dịch ít phải dịch đổi. Ví dụ, kiến trúc x86 của Intel/AMD là CISC, vốn có nhiều lệnh đa chức năng phức tạp.

**RISC (Reduced Instruction Set Computer)** là kiến trúc máy tính chỉ hỗ trợ một tập lệnh đơn giản và nhỏ gọn, mỗi lệnh thường thực hiện một thao tác đơn giản trong một clock cycle. Bằng cách giảm bớt độ phức tạp của lệnh, RISC cho phép phần cứng CPU đơn giản và nhanh hơn. Lệnh RISC có độ dài cố định, cho phép biên dịch nhanh và tạo điều kiện thực hiện các kỹ thuật tối ưu như pipelining. RISC phổ biến ở các CPU tiêu thụ điện năng thấp (ví dụ ARM, MIPS, Atmel AVR) và được dùng rộng rãi trong thiết bị di động, nhúng, vì mang lại hiệu năng cao trên mỗi watt công suất.



## 1.2 Ưu điểm và nhược điểm của từng kiến trúc

**CISC (Complex Instruction Set Computer)**
* ***Ưu điểm:*** CISC có mã chương trình ngắn hơn nhờ mỗi lệnh thực hiện được nhiều phép toán cùng lúc. Điều này giúp tiết kiệm bộ nhớ lưu trữ chương trình và giảm tải cho bộ biên dịch (compiler), vì lệnh cấp cao có thể được dịch thẳng sang một lệnh CISC phức tạp mà không phải ghép nhiều lệnh nhỏ. CISC còn là kiến trúc được ứng dụng lâu đời, nên có nhiều phần mềm và công cụ hỗ trợ (như dòng x86).

* ***Nhược điểm:*** Phần cứng CISC phức tạp vì phải có bộ giải mã lệnh đa dạng và có thể thực hiện nhiều bước nội bộ, làm giảm tốc độ thực thi lệnh. Việc giải mã lệnh phức tạp cũng làm tăng số chu kỳ xử lý cho mỗi lệnh (nhiều hơn một chu kỳ). Kiến trúc CISC đòi hỏi nhiều vi mạch và tiêu thụ điện năng cao hơn so với RISC. Kết quả là CPU CISC thường có tốc độ thực thi một lệnh đơn lâu hơn và khó áp dụng tối ưu kĩ thuật pipelining do độ dài lệnh thay đổi và tính đa dạng của lệnh.

**RISC (Reduced Instruction Set Computer)**
* ***Ưu điểm:*** RISC sử dụng tập lệnh đơn giản, mỗi lệnh thường được thực hiện trong một chu kỳ đồng hồ (clock cycle) duy nhất. Do vậy, CPU RISC có thể chạy ở xung nhịp cao hơn và dễ thiết kế pipeline hiệu quả. RISC tận dụng được số lượng register chung lớn hơn và giảm bớt truy cập bộ nhớ, giúp tốc độ xử lý nhanh và tiêu thụ điện năng thấp hơn so với CISC. Nhờ tính đơn giản, RISC thường được triển khai trong các thiết bị di động và nhúng, nơi tiết kiệm năng lượng là quan trọng.

* ***Nhược điểm:*** Do mỗi lệnh RISC đơn giản nên một nhiệm vụ phức tạp phải chia thành nhiều lệnh nhỏ, làm tăng số lệnh trên mỗi chương trình. Điều này khiến kích thước mã máy lớn hơn và cần nhiều bộ nhớ hơn để lưu trữ mã. Ngoài ra, RISC có thể đòi hỏi biên dịch phức tạp hơn vì phải ghép nhiều lệnh nhỏ để hoàn thành một lệnh mức cao hơn.



## 1.3 So sánh CISC và RISC theo các tiêu chí

### 1.3.1 Cấu trúc tập lệnh
* ***CISC:*** Tập lệnh CISC rất đa dạng và phức tạp. Lệnh CISC có thể có độ dài thay đổi và hỗ trợ nhiều chế độ địa chỉ cho tính toán khác nhau (gồm cả thanh ghi đến thanh ghi (REG to REG), bộ nhớ đến bộ nhớ (MEM to MEM), hoặc thanh ghi đến bộ nhớ (REG to MEM)). Ví dụ, một lệnh “MULT” trong CISC có thể nạp hai ô nhớ, nhân chúng và lưu kết quả chỉ trong một câu lệnh duy nhất. Điều này nghĩa là CISC hỗ trợ các lệnh thao tác trực tiếp trên bộ nhớ mà không cần chia nhỏ (memory-to-memory).

* ***RISC:*** Tập lệnh RISC ngắn và cố định độ dài, chỉ hỗ trợ REG to REG operations, chỉ gồm các lệnh đơn giản (chủ yếu là phép tính trên thanh ghi, nạp (LOAD) và lưu (STORE) dữ liệu). RISC dùng kiến trúc nạp/lưu: mọi phép toán phức tạp đều được thực hiện qua nhiều lệnh đơn; ví dụ, để nhân hai số, RISC phải thực hiện lệnh LOAD, sau đó lệnh tính toán (như ADD/PROD), rồi lệnh STORE. Các lệnh RISC đều có kích thước như nhau, giúp giải mã nhanh hơn. Do đó, RISC đơn giản hóa phần cứng giải mã (không cần microcode phức tạp) và tập trung vào phần mềm biên dịch.

### 1.3.2 Tốc độ xử lý
* ***CISC:*** Mỗi lệnh CISC thực hiện nhiều tác vụ có thể mất nhiều chu kỳ xung để giải mã và thực thi. Điều này làm cho số clock cycle cho mỗi lệnh cao hơn, dẫn đến tốc độ xử lý lệnh chậm hơn so với RISC. Ngoài ra, do lệnh phức tạp khó áp dụng kĩ thuật pipeline, hiệu năng tổng thể có thể bị hạn chế khi so sánh đơn vị thời gian trên lệnh mức cao so với RISC.

* ***RISC:*** Mỗi lệnh RISC được thiết kế để chạy trong một chu kỳ xung duy nhất. Nhờ vậy, CPU RISC có thể thực hiện được nhiều lệnh hơn mỗi giây. RISC cũng dễ triển khai pipeline vì tất cả lệnh có thời gian thực thi đồng nhất, giúp tăng hiệu năng thực thi tổng thể. Cách tiếp cận này làm giảm số chu kỳ cho mỗi lệnh mức cao, đổi lại chương trình có nhiều lệnh hơn (CISC giảm lệnh nhưng tăng số chu kỳ mỗi lệnh; RISC ngược lại). Kiến trúc RISC cho phép xử lý nhanh và tiêu thụ năng lượng thấp hơn vì có phần cứng giải mã đơn giản hơn.

### 1.3.3 Kích thước chương trình
* ***CISC:*** Do một lệnh CISC bao gồm nhiều phép tính, mã chương trình thường ngắn hơn và tiết kiệm bộ nhớ hơn. Ví dụ, phép tính nhân hai số trong CISC có thể dùng một lệnh duy nhất “MULT”, thay vì phải nạp, tính và lưu từng bước. Nhờ đó, CISC giảm được số dòng lệnh cần lưu và giảm dung lượng lưu trữ mã.

* ***RISC:*** Mỗi phép tính phức tạp được chia thành nhiều lệnh đơn giản, do đó mã chương trình dài hơn và chiếm nhiều bộ nhớ hơn. Nhiều tài liệu cho thấy RISC yêu cầu thêm không gian lưu trữ để chứa các lệnh phụ bổ sung cho mỗi tác vụ. Tuy nhiên, với chi phí bộ nhớ ngày nay giảm mạnh, nhược điểm về kích thước mã của RISC phần nào được giảm nhẹ, nhưng vẫn cần quan tâm khi bộ nhớ hạn chế.

### 1.3.4 Độ phức tạp phần cứng
* ***CISC:*** Thiết kế phần cứng CISC phức tạp vì phải hỗ trợ nhiều lệnh đa dạng và giải mã phức tạp (thường sử dụng bộ điều khiển vi chương (microcode)). Bộ xử lý CISC cần nhiều mạch giải mã, cần lưu các trạng thái tạm thời và vi mạch để thực hiện lệnh đa bước, khiến chip có kích thước lớn hơn và tốn điện hơn. Việc tối ưu thiết kế CISC cũng khó khăn hơn do nhiều chế độ địa chỉ và tính năng lệnh phức tạp.

* ***RISC:*** RISC đơn giản hóa phần cứng bằng cách giảm số lệnh và loại bỏ microcode. Lệnh RISC thường được giải mã trực tiếp (hardwired) và yêu cầu ít transistor hơn cho phần điều khiển. Nhờ đó, phần cứng RISC có thể bố trí thêm nhiều thanh ghi chung hơn (đa dạng thanh ghi to hơn) và các bộ thực thi phép toán tốc độ cao. Điều này khiến chip RISC thường nhỏ hơn, dễ phát triển và tiết kiệm năng lượng hơn so với CISC.

### 1.3.5 Ứng dụng thực tế (Intel, ARM, v.v.)
* ***CISC:*** Ứng dụng tiêu biểu nhất của CISC hiện nay là dòng vi xử lý Intel/AMD x86 dùng trong PC và server. Ngoài ra, các kiến trúc kinh điển như Motorola 68K, PDP-11, VAX cũng là CISC. CISC còn được dùng trong các bộ điều khiển máy tính lớn (mainframe) hay một số máy chơi game đời cũ yêu cầu xử lý phức tạp. Tuy nhiên, trong các hệ thống nhúng nhỏ gọn hiện đại, CISC ít được sử dụng hơn do tiêu thụ nhiều năng lượng và độ phức tạp cao.

* ***RISC:*** Nhiều kiến trúc phổ biến hiện nay là RISC. Tiêu biểu nhất là ARM – kiến trúc RISC chiếm lĩnh thị trường thiết bị di động, nhúng và IoT. ARM được sử dụng trong hầu hết smartphone, tablet, Raspberry Pi, Arduino và các thiết bị nhúng tiêu thụ điện thấp. Ngoài ra, các kiến trúc RISC khác như MIPS (được dùng trong một số bộ định tuyến, hệ thống nhúng và consoles trò chơi), SPARC (server/nghiên cứu) hay PowerPC (cũ, từng trong máy tính Apple trước khi chuyển sang Intel) cũng là những ví dụ nổi bật. Kiến trúc RISC-V mới nổi (được phát triển mở tại Đại học Berkeley) cũng đang được ứng dụng nhiều trong nhúng và vi xử lý thế hệ mới. Nói chung, CISC (Intel/AMD) thường thấy ở máy tính để bàn và server, còn RISC (ARM, MIPS, AVR, Power, RISC-V…) chiếm ưu thế ở thiết bị nhúng, di động và một số hệ thống công suất thấp.



## 1.4 Quan điểm: Kiến trúc nào phù hợp cho hệ thống nhúng?

Theo quan điểm của tôi, kiến trúc RISC phù hợp hơn với hệ thống nhúng hiện nay. Lý do chính là RISC tối ưu cho hiệu năng cao trong khi tiêu thụ điện năng thấp – điều rất quan trọng trong thiết bị nhúng giới hạn năng lượng và phải chạy liên tục. Các vi xử lý RISC (đặc biệt là ARM) đã chứng minh ưu thế của mình trong điện thoại di động, thiết bị IoT và nhúng. 
Ví dụ, theo Wikipedia: “...đến đầu thế kỷ 21, đa số hệ thống di động và low-end sử dụng RISC; kiến trúc ARM thống trị thị trường nhúng công suất thấp và chi phí thấp, được dùng trong Android, iPhone, Raspberry Pi, v.v.”. 

Kiến trúc RISC đơn giản cũng giúp bộ xử lý nhỏ gọn hơn, ít tỏa nhiệt và dễ thiết kế tiết kiệm chi phí. Trong khi đó, CISC như x86 thường đòi hỏi phần cứng phức tạp và tiêu thụ điện lớn hơn, ít thích hợp cho các thiết bị nhúng hạn chế tài nguyên. Hơn nữa, công nghệ hiện nay (bộ nhớ rẻ, compiler mạnh) đã giảm bớt nhược điểm về kích thước mã của RISC, khiến RISC trở nên lý tưởng cho hầu hết ứng dụng nhúng. Vì vậy, với xu hướng thiết bị di động và nhúng phát triển mạnh, RISC (như ARM hay RISC-V) đang là lựa chọn chủ đạo nhờ cân bằng tốt giữa hiệu suất và hiệu quả năng lượng.

Tóm lại, CISC và RISC đều có ưu – nhược điểm riêng. CISC cho mã ngắn và đa nhiệm phức tạp tốt, trong khi RISC cho tốc độ và hiệu suất năng lượng cao. Trong bối cảnh hiện nay của hệ thống nhúng, kiến trúc RISC tỏ ra phù hợp hơn nhờ tính đơn giản của lệnh, khả năng chạy nhanh và tiêu thụ điện thấp – điều phù hợp với yêu cầu của các thiết bị nhúng hiện đại.
