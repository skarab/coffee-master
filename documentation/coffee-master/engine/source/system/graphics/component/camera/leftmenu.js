function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6345\" class=\"headerLeftMenuInActive\"><a id=\"aID6345\" href=\"#\" OnMouseOver=\"link('_dir','camera0',this)\" class=\"leftMenuLinkHeadInActive\">camera</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID846\" class=\"leftMenuInActive\"><a id=\"aID846\" href=\"#\" OnMouseOver=\"link('_class','ComponentCamera54809',this)\" class=\"leftMenuLinkInActive\">ComponentCamera</a></div>\n");
document.write("<div id=\"divID847\" class=\"leftMenuInActive\"><a id=\"aID847\" href=\"#\" OnMouseOver=\"link('_class','ComponentCameraPerspective54809',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('ComponentCameraPerspective');\" onmouseout=\"return nd();\">ComponentCameraPerspectiv.<img src=\"../../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
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
