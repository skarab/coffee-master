/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 #  CLZ E%  �1.0    P   meta::ObjectPointer A<   5  	$   S    ��  graphics::Shader Ֆ  resourceK �]      S 6  �   	  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 0Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�    5 ZKtampL �# 	 ?  |t    � �pbasic:: H �:  Geometry"  Q�Fragment" &e
D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � 68�LineArray `String S  ��   #version 130 x ��%   uniform mat4 camera_to_local_matrix; 
6 �      varying vec2 uv;     �mat3 tbnC ! �vec3 eye_vector;    ! �float depth; � 1  l �void main() ��{           uv = gl_MultiTexCoord0.xy; N S   +0 � ?[0];  �1.xyz; 3 13 23 �3 23 bNormal+ �  �M4 &r = (gl_+ 2 -�0[3] 9) *�^  -� � M *> > S   2> �vec4 positb�odelViewD � 3; �  : �% == �.z;    0  Igl_PX 0Prov3ionY : 3; 4}  � !:/8 :"  "< /a
< "-
�#v$pa#exten �GL_ARB_t��_rectangle : enable� ��// Default helpers &� '��PPackDV(<5) (S)   3_areturn� / 2or(/ �/256.0, fract E); *b+| 1,  �m 5Unp � ~ -~ Z.   $~ ` 1.x*u + Uy); /o 0o R1   � 3� �( n 5) 2n  � n % u+1.0; 4a 5a 6=a � c 7c 8c -c 9c :c ;���ComputeParallax(L,,dheight `strengb<� =�N =� Fize(_ )S>   .; o # =s *l % -w  /2� ?p9uv+v S*h; @�d}    ATB   pQRGBE(MEv) C� D�� �exp = v.w*255.0-128� E_	�  �*exp2(exp); F�G� H
`#ifdef��EXT_gpu_st4 I   [� AAppl[2ows0col�� sampler2DRect s" ��lI�_softness,95) J� K��Roft = (B �>0.01); L� �� p*((1.0-/  )+ *� � (� �uv).x); M'NC�#endif O6 � 9� T baseR 3; QI( �* R* �* SC*  Fllic, T�, ProughE- U}- ��albedo; V    �3; W�
 � 3; X�
  � 4; YZZ]	[]	\]	]]		^� _]	 `�Xa   a^p�_k	� ���(�|,QC); b/ i ' c�// Write ��ed linear� ' d�0gl_�`Data[0	' =�;_ el f	l �@ layT D' =� 
�,')�22.0"h� N n
E = - 7; ip
m �*�7; jI
1
( =>5 k  # lT	\m\g  2g  i{ n�o%� emateri�p�	�   	� '� *�_q   NT yT OU �r`s� t u/  �[Flags+wH  T �x   y   z�1  |r X #~X �   �   �   �   �   �  W#� ��FaceCulling/ !EN"�TATE_FACE_CULLING~ �FrontPolygon< 	�POLYGON_MODE< OBack; $)QTestE�sd bool  1Fun�Z �TEST_FUNCTION[  �?ing^ �DW W� L� l�Q  N Fa�[ �BLENDING�<TOR_ pDestina� H "_AlphaW W"> �Threshold real C�v����� ���� �,�/ � � � ���S  ?� �� �?�  � #� � NTypef�PROPERTY_TYP�TValue�
FBjEvalua�Q gEVALUA��
S�   ��y� ���S�   ��z� ��� S�   � {� ��� S�   � |� ��� S�   � � ��/S�   �� �� ��� S�   ���� ��� S�   ���� ��� S�   ���� ��� S�   ���^c  c�& 3 1  �\ =�?   ��  �& # c	<  � n�R�	G B A �� � � ��  �9� ];[ ��S
�#= h;A  C �C 9�eC  BD �D  Q//D  
]) ?  � /�  �� �XmeterR�TEXTURE_PARAMETER�/��� /coffee/import/� #s/� �i �7�7
s7�7��7� 7�i �7 !-7�e5�5��5�� �i �5 �35 �d9� �9�93�919_�   )9� ;�k �; �5; &K<� �<�<3�<2<_�   *<� =�l ��           