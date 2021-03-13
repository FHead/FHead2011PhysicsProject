import xml.etree.ElementTree
DataRoot = xml.etree.ElementTree.parse('Centrality.xml').getroot()

import numpy as np

Data = []

for element in DataRoot.findall('cmsCondPayload/m-table/item'):
    if len(element.findall('bin-edge')) != 1:
        continue
    if len(element.findall('n-part')) != 1:
        continue
    if len(element.findall('n-coll')) != 1:
        continue
    if len(element.findall('b')) != 1:
        continue

    Entry = []
    Entry.append(float(element.find('bin-edge').text))
    Entry.append(float(element.find('n-part/mean').text))
    Entry.append(float(element.find('n-part/var').text))
    Entry.append(float(element.find('n-coll/mean').text))
    Entry.append(float(element.find('n-coll/var').text))
    Entry.append(float(element.find('b/mean').text))
    Entry.append(float(element.find('b/var').text))

    Data.append(Entry)

np.savetxt('Centrality.txt', Data, header='MinHFSum NPartMean NPartVar NCollMean NCollVar BMean BVar')
