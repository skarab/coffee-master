function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6333\" class=\"headerLeftMenuInActive\"><a id=\"aID6333\" href=\"#\" OnMouseOver=\"link('_dir','local_folder0',this)\" class=\"leftMenuLinkHeadInActive\">local_folder</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID829\" class=\"leftMenuInActive\"><a id=\"aID829\" href=\"#\" OnMouseOver=\"link('_class','LocalFolder35340',this)\" class=\"leftMenuLinkInActive\">LocalFolder</a></div>\n");
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
