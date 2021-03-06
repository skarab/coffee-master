/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 Y
  CLZ �  �1.0    P   meta::ObjectPointer A<   5  	$   S    �P  graphics::Shader �?  resourceK �]      S 6  �   �
  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 
p   Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |t�
    � �pbasic:: H �z  Geometry"  Q�Fragment" &�D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #v/�LineArray `String SB  ��   #version 130 x ��%   uniform mat4 camera_to_local_matrix; 
6 �	      varying vec2 uv;i � 3 eye_vector; C 	 1  7 �void main() Q{f �       uv = gl_MultiTexCoord0.xy; N S   0 �mat3 tbn� S   +  ?[0]X  �1.xyz; 3 13 23  u#3 23 bNormal+ � S   M4 /r = (gl_ 2 -�0[3] 9) *� ^ Z ^ �gl_Posit
�= ftrans�S(); w4} ; z/8 z"  < /�< S�  :�� � - Qexten �GL_ARB_t�_rectangle : enable !�// Default helpers "�  � � ��PackDepth(float d 5) $� 03Oareturn / 2or(/ �/256.0, fract E); &b'| (*m 5Unp � ~ )~ Z*   $~ ` 1.x*u + Uy); +o ,o -�� � �( n 5) .n Z/   n % u+1.0; 0a 1a 2�a � c 3c 4c -c 5c 6c 7.��ComputeParallax(�,|", bdheight `strengb8� 9�N v�� Fize(_ )� �.; o # =s *l % -w  /2� ;�9uv+v S*h; < d}    =T>   p@RGBEe4 v) ?�  )!� �exp = v.w*255.0-128� A�	� X�*exp2(exp); B�C� Db`#ifdef��EXT_gpu_s_t4 E   [� AAppl�2ows0col�� sampler2DRect s" ��lI�_softness,y5) F� G��  / " = (B �>0.01); H   H�� p*((1.0-/  )+ *� � (� �uv).x); I'J��#endif K6L�y� T baseR ;�"( V* N�* �albedo; O  4; P� Q�R�SC T� U�XV   a\p�_�� ��~(� z,� @); Wr
� �	1Col� (J p,�  ��z, 1.0)*H N % X�Y�Z [�?\  ��[Flags�	]H  �^   _   `2P !b�c   d   � ##�	�FaceCullingMod/!EN�
�TATE_FACE_CULLINGr �FrontPolygon< 	�POLYGON_MODE< OBack; $1QTestE�sd bool � @Func�Z �TEST_FUNCTION[ Writing^ D � lW  � L� lQ  � Fa�[ �BLENDING�<TOR_ pDestina� H "_AlphaW W"> �Threshold real �vfd
g�h ijCk" l m nkoG p" qbrS  ?s* t��?�  _ #� � NType�PROPERTY_TYP�TValue
��jEvalua�Q gEVALUA�u{qv   w  V_� �x�y��`� �{� |J c� �~�S   �� d� ��� S�   �\ H?�  c  ��& 3 M ! �\ =�?    ��  ��& # X<  � n�R�G B A �� � � ��   )\> �9� �	�[ ��D
�#=]//A  H

) |*?  � /� �� �
Xmeteri�TEXTURE_PARAMETER#�#/#1�  -� /coffee/import/� "s/� .� ��   �����- �-7e5�5��55�5��           