# RFC Doc :

## 1XX -> Error client side

- 101: Not authorized

## 3XX -> Error server side

### 31X -> Team / 32X -> Channel / 33X -> Thread / 34X -> Reply

- 3X1: Can't find uuid in database

- 3X2: Already exists

## 9XX -> Success command

### 91X -> Team / 92X -> Channel / 93X -> Thread / 94X -> Reply

- 911: Successfully created team

- 921: Successfully created channel

- 931: Successfully created thread

- 941: Successfully created reply
