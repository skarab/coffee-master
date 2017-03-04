function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6485\" class=\"headerLeftMenuInActive\"><a id=\"aID6485\" href=\"#\" OnMouseOver=\"link('_dir','editor_frame0',this)\" class=\"leftMenuLinkHeadInActive\">editor_frame</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1095\" class=\"leftMenuInActive\"><a id=\"aID1095\" href=\"#\" OnMouseOver=\"link('_class','EditorFrame22483',this)\" class=\"leftMenuLinkInActive\">EditorFrame</a></div>\n");
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
