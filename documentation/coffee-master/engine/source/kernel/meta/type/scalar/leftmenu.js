function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6314\" class=\"headerLeftMenuInActive\"><a id=\"aID6314\" href=\"#\" OnMouseOver=\"link('_dir','scalar0',this)\" class=\"leftMenuLinkHeadInActive\">scalar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID797\" class=\"leftMenuInActive\"><a id=\"aID797\" href=\"#\" OnMouseOver=\"link('_class','Scalar53261',this)\" class=\"leftMenuLinkInActive\">Scalar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Functions</div>\n");
document.write("<div id=\"divID2641\" class=\"leftMenuInActive\"><a id=\"aID2641\" href=\"#\" OnMouseOver=\"link('_member','SCALAR_FORMAT_GetFormat912955449',this)\" class=\"leftMenuLinkInActive\">SCALAR_FORMAT_GetFormat</a></div>\n");
document.write("<div id=\"divID2643\" class=\"leftMenuInActive\"><a id=\"aID2643\" href=\"#\" OnMouseOver=\"link('_member','SCALAR_FORMAT_GetFormatName771145812',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('SCALAR_FORMAT_GetFormatName');\" onmouseout=\"return nd();\">SCALAR_FORMAT_GetFormatNa.<img src=\"../../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
document.write("<div id=\"divID2642\" class=\"leftMenuInActive\"><a id=\"aID2642\" href=\"#\" OnMouseOver=\"link('_member','SCALAR_FORMAT_GetFormatSize771145812',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('SCALAR_FORMAT_GetFormatSize');\" onmouseout=\"return nd();\">SCALAR_FORMAT_GetFormatSi.<img src=\"../../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
document.write("<div id=\"divID2644\" class=\"leftMenuInActive\"><a id=\"aID2644\" href=\"#\" OnMouseOver=\"link('_member','SCALAR_FORMAT_GetType771145812',this)\" class=\"leftMenuLinkInActive\">SCALAR_FORMAT_GetType</a></div>\n");
document.write("<div id=\"divID2640\" class=\"leftMenuInActive\"><a id=\"aID2640\" href=\"#\" OnMouseOver=\"link('_member','SCALAR_FORMAT_Register429215',this)\" class=\"leftMenuLinkInActive\">SCALAR_FORMAT_Register</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6217\" class=\"leftMenuInActive\"><a id=\"aID6217\" href=\"#\" OnMouseOver=\"link('_member','SCALAR_FORMAT240823',this)\" class=\"leftMenuLinkInActive\">SCALAR_FORMAT</a></div>\n");
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
