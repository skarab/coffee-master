/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 �
  CLZ   �1.0    P   meta::ObjectPointer A<   5  	$   S    �  graphics::Shader �  resourceK �]      S 6  �   �  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 
 %0Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |t�    � �pbasic:: H ��   Geometry" �h  Fragment" <D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � ��LineArray `String ��  �   #version 130 x � v�void main() 
��{    0       gl_PositC = �ModelViewMatrix*gl_� 3; B 4} i � /d� �0  [   � P   + Qexten �GL_EXT_gT!_s��4: enable s �       uniform vec4 light_p� 0;  p& �int depth_pass; O E ES   !E�vec3 ns[3]; � // Normals  l 1) d(  ) PDirec� �s toward� C   #* c    ( �// Compute nh � at each v��.      ?0 �ns[0] = cross(��In[2].xyz- 0 �,      6� 
0OIn[4= j);   � 1� H 2� � 
0= � � 2� H 4� ^    4� G	4� ) !�^"   3�d
Q from�0ice �#]; d�
��  /w*�  $O 1O #2O %O 2O #4O &�W'   51�heck if the�� triangle fa2&he3 5H= �if (!(dot(,Cs)>0 ||  1 1 2 2 �)) )   �return; *�� �%� �P caps� �z-fail mode� W,   � �c==0) -/  �{   .   �  n!ea^ # /���BProjf�	;D 3Emi�_(); 1b ,_2]; 2b 
3b ,_4]; 4b 
5 �ndPrimitive  6C  . 7sFr  8   l�  �(�-?o,0); 9� 
:� B4� 
;� 
<� B2� 
=� 
_>   G   ?�3} @�
G   A	�// Loop over all edges and extrude�`needed�RB   < Pfor (}�i=0; i<3; i++) C�	�D-11ind!ob eighbor
 m E� m �v0 = i*2� [F     �nb = (i*2+1GT		D 1$ �2) % 6; H1_I   N� n	%at�,��*exact* same way as done above!   J   V 
��   K   ;! �/nb�v�L~C /v1C 5M� 1� N� e %nb� O� 0C � P� 2� Q� e %v1� R� �1� S_ i9_
F	8	@, ag%"asJ U�A L	&vM	VT Q	$%nbT WT V	$%v1T XW	ZY   `FE� � � ��it does not have aoB, or# �'s a possible silhouettmXZ   *D>f (� `w<1e-3v	;  [?  �	-3) \�V  _ �2j !//-q a quad8b
Pstrip� ^^   A��vp	_�� �tk C0�/ -S  , Ga� b	1_1]; ck d	G1	e�� �f3_g�W}   h�  iqjh8+"  kV lN m+?n  ��[Flags�o�Pp   qH L $sH  ��##k�FaceCulling�/ !EN��TATE_FACE_CULLINGj �FrontPolygon< 	�POLYGON_MODE< OBack; $D�QTestE�sd bool + 1Fun�Z �TEST_FUNCTION[ Writing^ �W �� L� OlendQ  �oFactor[ �BLENDING�<TOR_ pDestina� H "_AlphaW W"> �Threshold real _Colorv�u   ����v�w xy!z D !| � ~  ���! ?� S�   �{?�  " #� �NType��PROPERTY_TYP�TValued
��jEvalua�Q gEVALUA��� S�   ��q� ��� ��   �   .� ?�  c  �
f& + a<  � nQR�G B A �h� � &�   � >�  7����������    