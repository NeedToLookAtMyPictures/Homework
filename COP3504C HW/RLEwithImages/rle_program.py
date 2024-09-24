from inspect import Attribute

import console_gfx
import binascii

def count_runs(flatData): # works
      if len(flatData) == 0:
            return 0
      count = 1
      length = 0
      tracker = flatData[0]
      for i in flatData:
            if tracker != i:
                  tracker = i
                  count += 1
            else:
                  length += 1
            if length >= 16:
                  count += 1
                  length = 0
      return count

def to_hex_string(data): # works
      hexOut = ""
      for i in data:
            if isinstance(i, int):
                  if i > 9:
                        ascee = 97 + (i % 10)
                        hexOut += chr(ascee)
                  else:
                        hexOut += str(i)
            else: # already an alpha char (i.e. hex format)
                  hexOut += i
      return hexOut

def encode_rle(flat_data): # works
      count = 0
      track = flat_data[0] # data point being counted
      hexList = []
      for i in range(len(flat_data)):
            if track == flat_data[i] and count < 15:
                  count += 1
            elif track == flat_data[i]:
                  hexList.append(count)
                  hexList.append(track)
                  count = 1
            else:
                  hexList.append(count)
                  hexList.append(track)
                  track = flat_data[i]
                  count = 1
      hexList.append(count) # captures very last elements in the list
      hexList.append(track)
      encodeList = bytearray(hexList)
      return encodeList

def get_decoded_length(rle_data): # works
      rle_data.lower()
      count = 0
      for i in range(0, len(rle_data) - 1, 2):
            try:
                  count += int(rle_data[i])
            except ValueError:
                  charVal = (ord(rle_data[i].lower()) - ord('a') + 10)
                  count += charVal
      return count

def decode_rle(rle_data): # broken
      nCoded_rle = bytearray()
      for i in range(0, len(rle_data), 2):
            try:
                  count = int(rle_data[i])
            except (AttributeError, ValueError):
                  count = ord(rle_data[i]) - ord('a') + 10
            finally:
                  count = int(count)
                  try:
                        run = int(rle_data[i + 1])
                  except ValueError:
                        run = ord(rle_data[i + 1]) - ord('a') + 10
                  finally:
                        byte = bytes([run])
                        for j in range(count):
                              nCoded_rle = nCoded_rle + byte

      return nCoded_rle

def string_to_data(data_string): # works
      output = bytearray()
      for i in data_string:
            output.append(int(i, 16))
      return output

def to_rle_string(rleData): # works
      rleData.lower()
      output = ''
      for i in range(len(rleData)):
            if i % 2 == 0:
                  output += str(rleData[i])
            else:
                  if rleData[i] >= 10:
                        char = chr(rleData[i] - 10 + ord('a'))
                        output += char
                  else:
                        output += str(rleData[i])
                  if i < len(rleData) - 1:
                        output += ':'
      return output

def string_to_rle(rleString): # works
      rleString.lower()
      splitUp = rleString.split(':')
      rleList = []
      for i in splitUp:
            if len(i) % 2 == 0:
                  rleList.append(i[0])
                  rleList.append(i[1])
            else:
                  rleList.append(i[:2])
                  index = len(rleList) - 1
                  rleList[index] = chr(int(rleList[index]) - 10 + ord('a'))
                  rleList.append(i[2])
      return string_to_data(rleList)

def case_7(data, alreadyRLE = False):
      if alreadyRLE:
            output = []
            for i in range(len(data)):
                  if i % 2 == 0:
                        output += str(data[i])
                  else:
                        output += str(data[i])
                        if i < len(data) - 1:
                              output += ':'
            output = [i.lower() for i in output]
            for i in range(0, len(output), 3):
                  try:
                        output[i] = int(output[i])
                        output[i] = str(output[i])
                  except:
                        output[i] = str(ord(output[i]) - ord('a') + 10)
            output = ''.join(output)
            RLEstring = output
      else:
            RLE = encode_rle(data)
            RLEstring = to_rle_string(RLE)
      return RLEstring

def case_8(data, alreadyRLE = False):
      if alreadyRLE:
            RLEhex = data
      else:
            RLE = encode_rle(data)
            RLEhex = to_hex_string(RLE)
      return RLEhex

def case_9(data, alreadyRLE = False):
      if alreadyRLE:
            RLEdecode = decode_rle(data)
      else:
            RLE = encode_rle(data)
            RLEdecode = decode_rle(RLE)
      hex_string = RLEdecode.hex() # I am in pain, removes extraneous zeros from bytearray output (0e0f0001) == (ef01)
      formatted_output = hex_string.replace('0f','f').replace('0e','e').replace('0d','d').replace('0c','c').replace('0b','b').replace('0a','a').replace('09','9').replace('08','8').replace('07','7').replace('06','6').replace('05','5').replace('04','4').replace('03','3').replace('02','2').replace('01','1').replace('00','0')
      FLAThex = formatted_output
      return FLAThex

currentData = None
isRLE = False
def main():
      global currentData
      global isRLE
      print("\nRLE Menu"
            "\n--------"
            "\n0. Exit"
            "\n1. Load File"
            "\n2. Load Test Image"
            "\n3. Read RLE String"
            "\n4. Read RLE Hex String"
            "\n5. Read Data Hex String"
            "\n6. Display Image"
            "\n7. Display RLE String"
            "\n8. Display Hex RLE Data"
            "\n9. Display Hex Flat Data")

      option = input("\nSelect a Menu Option: ")
      accept = ["0","1","2","3","4","5","6","7","8","9"]
      if option not in accept:
            print("Error! Invalid input.")
            main()
      match option:
            case "0":
                  exit()
            case "1":
                  # Accepts a filename from the user and invokes console_gfx.load_file
                  fileName = input("Enter name of file to load: ")
                  currentData = console_gfx.load_file(fileName)
                  isRLE = False
                  main()
            case "2":
                  # Loads console_gfx.TEST_IMAGE
                  currentData = console_gfx.TEST_IMAGE
                  print('Test image data loaded.')
                  isRLE= False
                  main()
            case "3":
                  # Reads RLE data from the user in decimal notation with delimiters
                  currentData = input("Enter an RLE string to be decoded: ")
                  currentData = [i for i in currentData if i != ":"] # remove delimiter
                  currentData = "".join(currentData) # join together
                  isRLE = True
                  main()
            case "4":
                  # Reads RLE data from the user in hexadecimal notation without delimiters
                  currentData = input("Enter the hex string holding RLE data: ")
                  print(f'RLE decoded length: {get_decoded_length(currentData)}')
                  isRLE = True
                  main()
            case "5":
                  # Reads raw (flat) data from the user in hexadecimal notation
                  currentData = input("Enter the hex string holding flat data: ")
                  print(f'Numbers of runs: {count_runs(currentData)}')
                  isRLE = False
                  main()
            case "6":
                  print("Displaying image...")
                  if currentData is None:
                        print("(no data)")
                  else:
                        console_gfx.display_image(currentData)
                  main()
            case "7":
                  # Converts the current data into a human-readable RLE representation (with delimiters):
                  if currentData is None:
                        print("RLE representation: (no data)")
                  else:
                        if isRLE: # it is already in RLE form
                              print(f'RLE representation: {case_7(currentData, True)}')
                        else:
                              print(f'RLE representation: {case_7(currentData)}')

                  main()
            case "8":
                  # Converts the current data into RLE hexadecimal representation (without delimiters)
                  if currentData is None:
                        print("RLE hex values: (no data)")
                  else:
                        if isRLE: # skip RLE encoding step since it is already RLE
                              print(f'RLE representation: {case_8(currentData.lower(), True)}')
                        else:
                              print(f'RLE hex values: {case_8(currentData)}')
                  main()
            case "9":
                  # Displays the current raw (flat) data in hexadecimal representation (without delimiters)
                  if currentData is None:
                        print("Flat hex values: (no data)")
                  else:
                        if isRLE:
                              print(f'Flat hex values: {case_9(currentData.lower(), True)}')
                        else:
                              print(f'Flat hex values: {case_9(currentData)}')
                  main()



if __name__ == '__main__':
      print("Welcome to the RLE image encoder!"
            "\n\nDisplaying Spectrum Image:")
      console_gfx.display_image(console_gfx.TEST_RAINBOW)
      print()
      main()