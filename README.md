# C++ Game Programming

## 📌 프로젝트 개요
이 프로젝트는 Youtube에서 제공하는 전북대학교의 **"C++ 프로그래밍, 게임 만들기 실습"** 강의를 참고하여 진행되었습니다.

🔗 **강의 링크:** [C++ 프로그래밍, 게임 만들기 실습](https://www.youtube.com/playlist?list=PLMcUoebWMS1muMsyLM6K7uGBIjzDKKUF-)

---

## 🛠 C++ 게임 프로그래밍 환경 설정

### 1️⃣ **Visual Studio 및 SFML 설치**
1. **Visual Studio 2022 커뮤니티 버전 다운로드 및 설치**  
   🔗 [다운로드 링크](https://visualstudio.microsoft.com/ko/downloads/)
2. **SFML 다운로드** (최신 버전)  
   🔗 [SFML 공식 사이트](https://www.sfml-dev.org/download/)  
   → **Visual C++ 17 (2022) 64-bit** 버전 다운로드

### 2️⃣ **Visual Studio 프로젝트 생성 및 초기 설정**
1. **빈 프로젝트 만들기** (솔루션 및 프로젝트를 같은 디렉토리에 배치하는 옵션 해제)
2. **SFML 라이브러리 복사**
   - 다운로드한 SFML 폴더에서 `lib`, `include` 폴더를 **솔루션 파일이 있는 위치에 복사**
   - 추가 리소스 파일 다운로드 및 복사 (강의 영상에서 제공)
     🔗 [resource 폴더 다운로드](https://drive.google.com/file/d/1PUGn6n9zhKt6ATJJjizZEg5s0MG4VCEB/view)

---

## ⚙️ Visual Studio 프로젝트 설정

### 1️⃣ **출력 및 중간 디렉토리 설정**
- **프로젝트 우클릭 → 속성** (솔루션이 아니라 프로젝트 클릭!)
- **구성**: `모든 구성`, **플랫폼**: `x64`
- **구성 속성 → 일반 → 출력 디렉토리** (기존 내용 지우고 아래 내용)
  ```
  $(ProjectDir)\..\..\Build\$(Platform)$(Configuration)\
  ```
- **구성 속성 → 일반 → 중간 디렉토리** (기존 내용 지우고 아래 내용)
  ```
  $(ProjectDir)\..\..\Output\$(Platform)$(Configuration)\$(ProjectName)\
  ```
- **우측 아래 "적용" 클릭**

### 2️⃣ **SFML 경로 추가**
- **SFML include 경로 추가**  
  **구성 속성 → C/C++ → 일반 → 추가 포함 디렉토리**
  ```
  $(SolutionDir)\include
  ```
- **SFML lib 경로 추가**  
  **구성 속성 → 링커 → 일반 → 추가 라이브러리 디렉토리**
  ```
  $(SolutionDir)\lib
  ```
- **우측 아래 "적용" 클릭**

### 3️⃣ **Debug 모드에서 추가 종속성 설정**
- **구성 속성 → 링커 → 입력 → 추가 종속성**
  - 기존 내용을 지우지 않고, 아래 내용을 추가 (기존 내용 : $(CoreLibraryDependencies);%(AdditionalDependencies))
  ```
  sfml-graphics-s-d.lib;sfml-system-s-d.lib;sfml-window-s-d.lib;opengl32.lib;winmm.lib;gdi32.lib;freetype.lib;
  ```

### 4️⃣ **SFML Static 설정**
- **구성 속성 → C/C++ → 전처리기 → 전처리기 정의**
  - 기존 내용을 지우지 않고, 아래 내용을 추가 (기존 내용 : _DEBUG;_CONSOLE;%(PreprocessorDefinitions))
  ```
  SFML_STATIC;
  ```
---
