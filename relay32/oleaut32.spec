name oleaut32
type win32

1 stub DllGetClassObject
2 stdcall SysAllocString(wstr) SysAllocString32
3 stdcall SysReAllocString(ptr wstr) SysReAllocString32
4 stdcall SysAllocStringLen(wstr long) SysAllocStringLen32
5 stdcall SysReAllocStringLen(ptr ptr long) SysReAllocStringLen32
6 stdcall SysFreeString(wstr) SysFreeString32
7 stdcall SysStringLen(wstr) SysStringLen32
8 stub VariantInit
9 stub VariantClear
10 stub VariantCopy
11 stub VariantCopyInd
12 stub VariantChangeType
13 stub VariantTimeToDosDateTime
14 stub DosDateTimeToVariantTime
15 stub SafeArrayCreate
16 stub SafeArrayDestroy
17 stub SafeArrayGetDim
18 stub SafeArrayGetElemsize
19 stub SafeArrayGetUBound
20 stub SafeArrayGetLBound
21 stub SafeArrayLock
22 stub SafeArrayUnlock
23 stub SafeArrayAccessData
24 stub SafeArrayUnaccessData
25 stub SafeArrayGetElement
26 stub SafeArrayPutElement
27 stub SafeArrayCopy
28 stub DispGetParam
29 stub DispGetIDsOfNames
30 stub DispInvoke
31 stub CreateDispTypeInfo
32 stub CreateStdDispatch
33 stub RegisterActiveObject
34 stub RevokeActiveObject
35 stub GetActiveObject
36 stub SafeArrayAllocDescriptor
37 stub SafeArrayAllocData
38 stub SafeArrayDestroyDescriptor
39 stub SafeArrayDestroyData
40 stub SafeArrayRedim
41 stub OACreateTypeLib2
46 stub VarParseNumFromStr
47 stub VarNumFromParseNum
48 stub VarI2FromUI1
49 stub VarI2FromI4
50 stub VarI2FromR4
51 stub VarI2FromR8
52 stub VarI2FromCy
53 stub VarI2FromDate
54 stub VarI2FromStr
55 stub VarI2FromDisp
56 stub VarI2FromBool
58 stub VarI4FromUI1
59 stub VarI4FromI2
60 stub VarI4FromR4
61 stub VarI4FromR8
62 stub VarI4FromCy
63 stub VarI4FromDate
64 stub VarI4FromStr
65 stub VarI4FromDisp
66 stub VarI4FromBool
68 stub VarR4FromUI1
69 stub VarR4FromI2
70 stub VarR4FromI4
71 stub VarR4FromR8
72 stub VarR4FromCy
73 stub VarR4FromDate
74 stub VarR4FromStr
75 stub VarR4FromDisp
76 stub VarR4FromBool
78 stub VarR8FromUI1
79 stub VarR8FromI2
80 stub VarR8FromI4
81 stub VarR8FromR4
82 stub VarR8FromCy
83 stub VarR8FromDate
84 stub VarR8FromStr
85 stub VarR8FromDisp
86 stub VarR8FromBool
88 stub VarDateFromUI1
89 stub VarDateFromI2
90 stub VarDateFromI4
91 stub VarDateFromR4
92 stub VarDateFromR8
93 stub VarDateFromCy
94 stub VarDateFromStr
95 stub VarDateFromDisp
96 stub VarDateFromBool
98 stub VarCyFromUI1
99 stub VarCyFromI2
100 stub VarCyFromI4
101 stub VarCyFromR4
102 stub VarCyFromR8
103 stub VarCyFromDate
104 stub VarCyFromStr
105 stub VarCyFromDisp
106 stub VarCyFromBool
108 stub VarBstrFromUI1
109 stub VarBstrFromI2
110 stub VarBstrFromI4
111 stub VarBstrFromR4
112 stub VarBstrFromR8
113 stub VarBstrFromCy
114 stub VarBstrFromDate
115 stub VarBstrFromDisp
116 stub VarBstrFromBool
118 stub VarBoolFromUI1
119 stub VarBoolFromI2
120 stub VarBoolFromI4
121 stub VarBoolFromR4
122 stub VarBoolFromR8
123 stub VarBoolFromDate
124 stub VarBoolFromCy
125 stub VarBoolFromStr
126 stub VarBoolFromDisp
130 stub VarUI1FromI2
131 stub VarUI1FromI4
132 stub VarUI1FromR4
133 stub VarUI1FromR8
134 stub VarUI1FromCy
135 stub VarUI1FromDate
136 stub VarUI1FromStr
137 stub VarUI1FromDisp
138 stub VarUI1FromBool
146 stub DispCallFunc
147 stub VariantChangeTypeEx
148 stub SafeArrayPtrOfIndex
149 stub SysStringByteLen
150 stub SysAllocStringByteLen
160 stub CreateTypeLib
161 stdcall LoadTypeLib (ptr ptr) LoadTypeLib32
162 stub LoadRegTypeLib 
163 stdcall RegisterTypeLib(ptr str str) RegisterTypeLib32
164 stdcall QueryPathOfRegTypeLib(ptr long long long ptr) QueryPathOfRegTypeLib32
165 stub LHashValOfNameSys
166 stub LHashValOfNameSysA
170 stdcall OaBuildVersion() OaBuildVersion
171 stub ClearCustData
180 stub CreateTypeLib2
183 stub LoadTypeLibEx
184 stub SystemTimeToVariantTime
185 stub VariantTimeToSystemTime
186 stub UnRegisterTypeLib
190 stub VarDecFromUI1
191 stub VarDecFromI2
192 stub VarDecFromI4
193 stub VarDecFromR4
194 stub VarDecFromR8
195 stub VarDecFromDate
196 stub VarDecFromCy
197 stub VarDecFromStr
198 stub VarDecFromDisp
199 stub VarDecFromBool
200 stub GetErrorInfo
201 stub SetErrorInfo
202 stub CreateErrorInfo
205 stub VarI2FromI1
206 stub VarI2FromUI2
207 stub VarI2FromUI4
208 stub VarI2FromDec
209 stub VarI4FromI1
210 stub VarI4FromUI2
211 stub VarI4FromUI4
212 stub VarI4FromDec
213 stub VarR4FromI1
214 stub VarR4FromUI2
215 stub VarR4FromUI4
216 stub VarR4FromDec
217 stub VarR8FromI1
218 stub VarR8FromUI2
219 stub VarR8FromUI4
220 stub VarR8FromDec
221 stub VarDateFromI1
222 stub VarDateFromUI2
223 stub VarDateFromUI4
224 stub VarDateFromDec
225 stub VarCyFromI1
226 stub VarCyFromUI2
227 stub VarCyFromUI4
228 stub VarCyFromDec
229 stub VarBstrFromI1
230 stub VarBstrFromUI2
231 stub VarBstrFromUI4
232 stub VarBstrFromDec
233 stub VarBoolFromI1
234 stub VarBoolFromUI2
235 stub VarBoolFromUI4
236 stub VarBoolFromDec
237 stub VarUI1FromI1
238 stub VarUI1FromUI2
239 stub VarUI1FromUI4
240 stub VarUI1FromDec
241 stub VarDecFromI1
242 stub VarDecFromUI2
243 stub VarDecFromUI4
244 stub VarI1FromUI1
245 stub VarI1FromI2
246 stub VarI1FromI4
247 stub VarI1FromR4
248 stub VarI1FromR8
249 stub VarI1FromDate
250 stub VarI1FromCy
251 stub VarI1FromStr
252 stub VarI1FromDisp
253 stub VarI1FromBool
254 stub VarI1FromUI2
255 stub VarI1FromUI4
256 stub VarI1FromDec
257 stub VarUI2FromUI1
258 stub VarUI2FromI2
259 stub VarUI2FromI4
260 stub VarUI2FromR4
261 stub VarUI2FromR8
262 stub VarUI2FromDate
263 stub VarUI2FromCy
264 stub VarUI2FromStr
265 stub VarUI2FromDisp
266 stub VarUI2FromBool
267 stub VarUI2FromI1
268 stub VarUI2FromUI4
269 stub VarUI2FromDec
270 stub VarUI4FromUI1
271 stub VarUI4FromI2
272 stub VarUI4FromI4
273 stub VarUI4FromR4
274 stub VarUI4FromR8
275 stub VarUI4FromDate
276 stub VarUI4FromCy
277 stub VarUI4FromStr
278 stub VarUI4FromDisp
279 stub VarUI4FromBool
280 stub VarUI4FromI1
281 stub VarUI4FromUI2
282 stub VarUI4FromDec
283 stub BSTR_UserSize
284 stub BSTR_UserMarshal
285 stub BSTR_UserUnmarshal
286 stub BSTR_UserFree
287 stub VARIANT_UserSize
288 stub VARIANT_UserMarshal
289 stub VARIANT_UserUnmarshal
290 stub VARIANT_UserFree
291 stub LPSAFEARRAY_UserSize
292 stub LPSAFEARRAY_UserMarshal
293 stub LPSAFEARRAY_UserUnmarshal
294 stub LPSAFEARRAY_UserFree
295 stub LPSAFEARRAY_Size
296 stub LPSAFEARRAY_Marshal
297 stub LPSAFEARRAY_Unmarshal
320 stub DllRegisterServer
321 stub DllUnregisterServer
330 stub VarDateFromUdate
331 stub VarUdateFromDate
332 stub GetAltMonthNames
380 stub UserHWND_from_local
381 stub UserHWND_to_local
382 stub UserHWND_free_inst
383 stub UserHWND_free_local
384 stub UserBSTR_from_local
385 stub UserBSTR_to_local
386 stub UserBSTR_free_inst
387 stub UserBSTR_free_local
388 stub UserVARIANT_from_local
389 stub UserVARIANT_to_local
390 stub UserVARIANT_free_inst
391 stub UserVARIANT_free_local
392 stub UserEXCEPINFO_from_local
393 stub UserEXCEPINFO_to_local
394 stub UserEXCEPINFO_free_inst
395 stub UserEXCEPINFO_free_local
396 stub UserMSG_from_local
397 stub UserMSG_to_local
398 stub UserMSG_free_inst
399 stub UserMSG_free_local
410 stub DllCanUnloadNow
411 stub SafeArrayCreateVector
412 stub SafeArrayCopyData
413 stub VectorFromBstr
414 stub BstrFromVector
415 stub OleIconToCursor
416 stub OleCreatePropertyFrameIndirect
417 stub OleCreatePropertyFrame
418 stub OleLoadPicture
419 stub OleCreatePictureIndirect
420 stub OleCreateFontIndirect
421 stub OleTranslateColor
422 stub OleLoadPictureFile
423 stub OleSavePictureFile
424 stub OleLoadPicturePath
