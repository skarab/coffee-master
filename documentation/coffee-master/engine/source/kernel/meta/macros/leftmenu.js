function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6305\" class=\"headerLeftMenuInActive\"><a id=\"aID6305\" href=\"#\" OnMouseOver=\"link('_dir','macros0',this)\" class=\"leftMenuLinkHeadInActive\">macros</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Macros</div>\n");
document.write("<div id=\"divID618\" class=\"leftMenuInActive\"><a id=\"aID618\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Ancestor803574586',this)\" class=\"leftMenuLinkInActive\">COFFEE_Ancestor</a></div>\n");
document.write("<div id=\"divID619\" class=\"leftMenuInActive\"><a id=\"aID619\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Attribute873390491',this)\" class=\"leftMenuLinkInActive\">COFFEE_Attribute</a></div>\n");
document.write("<div id=\"divID620\" class=\"leftMenuInActive\"><a id=\"aID620\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_AttributeCustom2742730669',this)\" class=\"leftMenuLinkInActive\">COFFEE_AttributeCustom</a></div>\n");
document.write("<div id=\"divID617\" class=\"leftMenuInActive\"><a id=\"aID617\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_BeginType954307159',this)\" class=\"leftMenuLinkInActive\">COFFEE_BeginType</a></div>\n");
document.write("<div id=\"divID621\" class=\"leftMenuInActive\"><a id=\"aID621\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_EndType1854416906',this)\" class=\"leftMenuLinkInActive\">COFFEE_EndType</a></div>\n");
document.write("<div id=\"divID615\" class=\"leftMenuInActive\"><a id=\"aID615\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_RegisterType1049939645',this)\" class=\"leftMenuLinkInActive\">COFFEE_RegisterType</a></div>\n");
document.write("<div id=\"divID610\" class=\"leftMenuInActive\"><a id=\"aID610\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_SerializeObject3240461139',this)\" class=\"leftMenuLinkInActive\">COFFEE_SerializeObject</a></div>\n");
document.write("<div id=\"divID612\" class=\"leftMenuInActive\"><a id=\"aID612\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_SerializeScalar161482319',this)\" class=\"leftMenuLinkInActive\">COFFEE_SerializeScalar</a></div>\n");
document.write("<div id=\"divID614\" class=\"leftMenuInActive\"><a id=\"aID614\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_SerializeScalarArray2856431989',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('COFFEE_SerializeScalarArray');\" onmouseout=\"return nd();\">COFFEE_SerializeScalarArr.<img src=\"../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
document.write("<div id=\"divID613\" class=\"leftMenuInActive\"><a id=\"aID613\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_SerializeScalarArrayFormat434658082',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('COFFEE_SerializeScalarArrayFormat');\" onmouseout=\"return nd();\">COFFEE_SerializeScalarArr.<img src=\"../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
document.write("<div id=\"divID611\" class=\"leftMenuInActive\"><a id=\"aID611\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_SerializeScalarFormat50205428',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('COFFEE_SerializeScalarFormat');\" onmouseout=\"return nd();\">COFFEE_SerializeScalarFor.<img src=\"../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
document.write("<div id=\"divID616\" class=\"leftMenuInActive\"><a id=\"aID616\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Type954307159',this)\" class=\"leftMenuLinkInActive\">COFFEE_Type</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Defines</div>\n");
document.write("<div id=\"divID622\" class=\"leftMenuInActive\"><a id=\"aID622\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_FindType360285606',this)\" class=\"leftMenuLinkInActive\">COFFEE_FindType</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
