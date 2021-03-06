/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 N
  CLZ   �1.0    P   meta::ObjectPointer A<   5  	$   S    �A  graphics::Shader �0  resourceK �]      S 6  �   �  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 
p   Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |t�    � �pbasic::U �  Geometry"  Q�Fragment" &9D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #/�LineArray `String S�  � �O// - M� !m  �� tonemapper v� " ss	� Y
f B�   #version 130    �   varying vec2 uv; " 1  / �void main() �{< �       uv = gl_MultiTexCoord0.xy; # ' �gl_Posit� �= ftransform(); Y 4} � /8 "  < /5< �  7   �Y +Df�F� [begin] � Y�NP   - Qexten �GL_ARB_t��_rectangle : enable S �   %   uni� sampler2DRect i�H ?; - � luminance-  r- �float brightness;�" �contrast; "�
  �gamma; #= Qexpos $�   �ye_adapta4; %&�'" 1(  I CGetEl E() )�S*   Jls 3 = !=2D(5,w �(0.5, 0.5)).x;�dR ereturn� j*(1.0-� u)+0.12*# 
 2 )/(� �+0.0001)); ,-� .��Dt; /( 0	 11  J�vec3 log10( Ev) 2'Z3   � �log2(v)/ e10); 4� 5] 6 7V  �7V t Xcolort �(��, uv).xyz; 9 ? c :    G **=�x; ;   )p Ald =
 (T82,  !);�linReferew0.18; =�' (og' �444.0; >	( G K S45; ?�� @LogC� 8; @� SA   X # �.rgb = (�c X*0.4/� T)/ld*z +� � )/1023.f; B   2` hclamp( 1@, 1.C�� �FilmLutWidth = 256; D�& @Padd� 
(5/4 4; EPSF   B7 �// Apply response lookup and1graT �	for target display G   N0+.r�t�Cmix(� 4,1-
  )�Mr; HV gV #gV IV bV #bV JUK'p �
C�Bvec4J�L�M@ N�O  � �?Q  ��[Flags�
RH  T S�@   U�C   W�X !YX  T�Z   [   \  ��2# $�FaceCullingMod !EN��TATE_FACE_CULLINGv �FrontPolygon< 	�POLYGON_MODE< OBack; $�DepthTestEBsd bool V @FunchZ �TEST_FUNCTION[ Writing^ 5 � lW �� L� OlendQ  �oFactor[ �BLENDING�<TOR_ aDestin\H "_AlphaW W"> �Threshold real �v�^   ����_�` a! b�#c �# f g �iSj ?k  j C�?�  P #� � NType �PROPERTY_TYP�TValuey
��jEvalua�Q gEVALUA�m� Pn   o�^� �p� q!  DU� �s�  du�V� �v� Sw   x�W� �y� z� JZ� �|�S}   ~+[� �� S�   �/\� ��� S�   ��  � jc  ��<��S���� +;E  s�C �C  �8C  5�@ �@ w� C �C  �AC  �
EI �I  �/,I  �
	{) MY?  � /� F�F�Parameter��TEXTURE_PARAMETERR�R-R�Z� /coffee/import/� ts/null.� �g ��c!4 �?lut*� �*�*3�*,*�S*5lut)�~
�) �0) !Pa�a��a�g ��           